// Memory segment structure

/*
  Author: Martin Eden
  Last mod.: 2024-06-02
*/

/*
  Data structures is the base substrate. Algorithms just spawn on them
  like plant species.
*/

#pragma once

#include <me_MemoryPoint.h>
#include <me_BaseTypes.h>

namespace me_MemorySegment
{
  using
    me_BaseTypes::TBool,
    me_BaseTypes::TUint_1,
    me_BaseTypes::TUint_2,
    me_BaseTypes::TChar;

  using
    me_MemoryPoint::TMemoryPoint;

  /*
    Memory span with byte granularity
  */
  struct TMemorySegment
  {
    union
    {
      TMemoryPoint Start;
      TUint_1 * Bytes;
    };
    TUint_2 Size;

    // Zeroing constructor
    TMemorySegment();

    // Print segment range to stdout
    void PrintWrappings();
    // Print raw bytes of memory in range to stdout
    void Print();

    // Get byte from segment by given offset
    TBool GetByte(TUint_1 * Byte, TUint_2 Offset);

    // Copy memory to another segment
    TBool CopyMemTo(TMemorySegment * Dest);
    // Copy memory from another segment
    TBool CopyMemFrom(TMemorySegment * Src);
    // Fill memory with zeroes
    void ZeroMem();

    // Reserve block of memory
    TBool Reserve(TUint_2 SegSize);
    // Release block of memory
    TBool Release();
  };

  // Describe ASCIIZ structure as memory segment
  TMemorySegment FromAsciiz(TChar * Asciiz);
  TMemorySegment FromAsciiz(const TChar * Asciiz); // <3 U C

  using me_MemoryPoint::TMemoryPoint_Bits;

  /*
    Memory span with bit granularity

    64 Kibit <Size> means maximum span is 8 KiB.
  */
  struct TMemorySegment_Bits
  {
    TMemoryPoint_Bits Start;
    TUint_2 Size;
  };
}

/*
  2024-05-17
  2024-05-23 GetByte
  2024-05-25 PrintWrappings, PrintMem, CopyMemTo, Spawn, Kill
  2024-05-27 ReserveChunk, ReleaseChunk, ZeroMem
  2024-05-30 CloneFrom
*/
