// Memory segment companion functions

/*
  Author: Martin Eden
  Last mod.: 2024-05-27
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
  Get byte from segment by given offset.

  Why

    Yes, you can read and modify any byte from segment like
    "Segment.Start.Bytes[0] = Segment.Start.Bytes[1]".
    And beyond segment.

    That's the problem. Lacking of implementation of conceptual
    integrity. Not because of security, not because of stability,
    but for design.

    Besides, your code will become simpler as you do not need
    to worry about checking range when getting data.
*/
TBool me_MemorySegment::GetByte(
  TUint_1 * Byte,
  TMemorySegment Segment,
  TUint_2 Offset
)
{
  const TUint_2 MaxUi2 = 0xFFFF;
  /*
    Offset is zero based, so offset 0xFFFF covers range of 0x10000 bytes.
    Size field can not hold that much.
  */
  if (Offset == MaxUi2)
    return false;

  if (Offset + 1 > Segment.Size)
    return false;

  *Byte = Segment.Start.Bytes[Offset];

  return true;
}

/*
  Print data describing memory segment to stdout.

  Useful for debug.

  We do not make any assumptions regarding memory described
  by segment. We do not try to read it.
*/
void TMemorySegment::PrintWrappings()
{
  printf(
    "[0x%04X](Start 0x%04X Size %d)",
    (TUint_2) this,
    this->Start.Addr,
    this->Size
    );
}

/*
  Print uncooked contents of memory segment to stdout.
*/
void TMemorySegment::PrintMem()
{
  for (TUint_2 Offset = 0; Offset < this->Size; ++Offset)
    fputc(this->Start.Bytes[Offset], stdout);
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
TBool me_MemorySegment::TMemorySegment::CopyMemTo(TMemorySegment Dest)
{
  TUint_2 Size = min(Dest.Size, this->Size);

  if (Size == 0)
    // Job done!
    return true;

  // Return false if data would intersect
  {
    TUint_2
      DestStart = Dest.Start.Addr,
      OurStart = this->Start.Addr;

    if (DestStart < OurStart)
    {
      TUint_2 DestFinish = Dest.Start.Addr + Size - 1;
      if (DestFinish >= OurStart)
        return false;
    }
    else if (OurStart <= DestStart)
    {
      TUint_2 OurFinish = this->Start.Addr + Size - 1;
      if (OurFinish >= DestStart)
        return false;
    }
  }

  for (TUint_2 Offset = 0; Offset < Size; ++Offset)
    Dest.Start.Bytes[Offset] = this->Start.Bytes[Offset];

  return true;
}

/*
  Copy memory _from_ another segment.

  Because I don't know which way of writing "copy" is right:
  CopyTo() or CopyFrom().

  Commutativeness is a nice property.
*/
TBool me_MemorySegment::TMemorySegment::CopyMemFrom(TMemorySegment Src)
{
  return Src.CopyMemTo((*this));
}

/*
  Allocate memory for structure

  We are allocating four bytes. Memory for structure.

  We are receiving address. We are writing to that address address
  of structure. I hate C.
*/
TBool me_MemorySegment::Spawn(TMemorySegment * * Segment)
{
  TUint_2 Addr = (TUint_2) malloc(sizeof(TMemorySegment));

  if (Addr == 0)
    return false;

  *Segment = (TMemorySegment*) Addr;

  (*Segment)->Start.Addr = 0;
  (*Segment)->Size = 0;

  // printf("Spawned [0x%04X].\n", Addr);

  return true;
}

// Deallocate memory with structure
TBool me_MemorySegment::Kill(TMemorySegment * Segment)
{
  if ((TUint_2) Segment == 0)
    return false;

  free(Segment);

  // printf("Killed [0x%04X].\n", (TUint_2) Segment);

  return true;
}

/*
  2024-05-23 GetByte
  2024-05-25 PrintWrappings, PrintMem, CopyMemTo, Spawn, Kill
*/
