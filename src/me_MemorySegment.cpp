// Memory segment companion functions

/*
  Author: Martin Eden
  Last mod.: 2024-06-01
*/

#include "me_MemorySegment.h"

#include <stdio.h> // printf() for Print()
#include <string.h> // strlen() for FromAsciiz()
#include <Arduino.h> // min() macro lol for CopyMemTo()

#include <me_BaseTypes.h>

using
  me_BaseTypes::TUint_1,
  me_BaseTypes::TUint_2,
  me_BaseTypes::TBool;

using
  me_MemorySegment::TMemorySegment;

/*
  Zeroing destructor

  Zeroing constructor is implemented via struct definition.

  Sometimes I hate C for their design decisions.

    Reducing coefficient at O(1) operation. Micromanagement at it's
    glory!

    Memory is not initialized, random values. So you can't read anything
    until you set fields.

    Upon destruction of object memory is not reset. Hello script kiddies
    skimming stack and heap for data.
*/
TMemorySegment::~TMemorySegment()
{
  Start.Addr = 0;
  Size = 0;
}

/*
  Print data describing memory segment to stdout.

  Useful for verification.

  We do not make any assumptions regarding memory described
  by segment. We do not try to read it.
*/
void TMemorySegment::PrintWrappings()
{
  printf("[TMemorySegment 0x%04X]", (TUint_2) this);
  printf("( Start ");
  Start.PrintWrappings();
  printf(" Size %u", Size);
  printf(" )");
}

/*
  Print uncooked contents of memory segment to stdout.
*/
void TMemorySegment::Print()
{
  for (TUint_2 Offset = 0; Offset < Size; ++Offset)
    fputc(Bytes[Offset], stdout);
}

/*
  Get byte from segment by given offset.

  Why

    Yes, you can read and modify any byte from segment like
    "Segment.Bytes[0] = Segment.Bytes[1]". And beyond segment.

    That's the problem. Lacking of implementation of conceptual
    integrity. Not because of security, not because of stability,
    but for design.

    Besides, your code will become simpler as you do not need
    to worry about checking range when getting data.
*/
TBool TMemorySegment::GetByte(TUint_1 * Byte, TUint_2 Offset)
{
  const TUint_2 MaxUi2 = 0xFFFF;
  /*
    Offset is zero based, so offset 0xFFFF covers range of 0x10000 bytes.
    Size field can not hold that much.
  */
  if (Offset == MaxUi2)
    return false;

  if (Offset + 1 > Size)
    return false;

  *Byte = Bytes[Offset];

  return true;
}

/*
  Describe ASCII structure as memory segment.

  What is called "string" in C is a pointer to zero-terminated
  sequence of bytes.

  This function describes span of that sequence. NOT including
  zero byte.
*/
TMemorySegment me_MemorySegment::FromAsciiz(TChar * Asciiz)
{
  TMemorySegment Result;

  Result.Start.Addr = (TUint_2) Asciiz;
  Result.Size = strlen(Asciiz);

  return Result;
}


// FromAsciiz() wrapper for typical use case .FromAsciiz("Literal")
TMemorySegment me_MemorySegment::FromAsciiz(const TChar * Asciiz)
{
  return FromAsciiz((TChar *) Asciiz);
}

/*
  Copy data to another segment.

  We DO NOT allocate any memory. We just copy data described
  by our segment to memory span described by destination segment.

  Destination segment may be shorter than ours.

  Post-condition: memory data in segment described by <Dest>
  is same as ours.

  ^ This means that <Dest> segment _may intersect_ with us as long
  as data do not intersect:

    .......  mem
       ~~    we    --> okay
     ~~~~~   them

    .......  mem
      ~~     we    --> nah
     ~~~~~   them
*/
TBool TMemorySegment::CopyMemTo(TMemorySegment Dest)
{
  TUint_2 MinSize = min(Dest.Size, Size);

  if (MinSize == 0)
    // Job done!
    return true;

  // Return false if data would intersect
  {
    TUint_2
      DestStart = Dest.Start.Addr,
      OurStart = Start.Addr;

    if (DestStart < OurStart)
    {
      TUint_2 DestFinish = Dest.Start.Addr + MinSize - 1;
      if (DestFinish >= OurStart)
        return false;
    }
    else if (OurStart <= DestStart)
    {
      TUint_2 OurFinish = Start.Addr + MinSize - 1;
      if (OurFinish >= DestStart)
        return false;
    }
  }

  for (TUint_2 Offset = 0; Offset < MinSize; ++Offset)
    Dest.Bytes[Offset] = Bytes[Offset];

  return true;
}

/*
  Copy memory _from_ another segment.

  Because I don't know which way of writing "copy" is right:
  CopyTo() or CopyFrom().

  Commutativeness is a nice property.
*/
TBool TMemorySegment::CopyMemFrom(TMemorySegment Src)
{
  return Src.CopyMemTo(*this);
}

/*
  Fill memory span with zero byte.

  We imply that memory is "ours", so we can write there
  whatever we please.

  This function is called from ReserveChunk() and ReleaseChunk().
*/
void TMemorySegment::ZeroMem()
{
  for (TUint_2 Offset = 0; Offset < Size; ++Offset)
    Bytes[Offset] = 0;
}

/*
  2024-05-23 GetByte
  2024-05-25 PrintWrappings, PrintMem, CopyMemTo, Spawn, Kill
  2024-05-30 CloneFrom
*/
