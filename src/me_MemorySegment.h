// Memory segment structure

/*
  Author: Martin Eden
  Last mod.: 2024-10-10
*/

/*
  Data structures is the base substrate. Algorithms grow on them
  like plant species.
*/

/*
  Central part of this module is memory segment definition.

  It's 1-D segment of memory addresses.

  It's pointer with size information.

  It's base datatype for all variable-length data.
*/

#pragma once

#include <me_MemoryPoint.h>
#include <me_BaseTypes.h>

namespace me_MemorySegment
{
  /*
    Memory span with byte granularity
  */
  struct TMemorySegment
  {
    union
    {
      me_MemoryPoint::TMemoryPoint Start = { .Addr = 0 };
      // "Bytes" provides array access to memory at "Start.Addr"
      TUint_1 * Bytes;
    };
    TUint_2 Size = 0;
  };

  /*
    Memory span with bit granularity

    64 Kibits is 8 KiB
  */
  struct TMemorySegment_Bits
  {
    me_MemoryPoint::TMemoryPoint_Bits Start;
    TUint_2 Size;
  };

  namespace Freetown
  {
    // [Debug] Print fields and data to stdout
    void PrintWrappings(TMemorySegment MemSeg);

    // Describe ASCIIZ structure as memory segment
    TMemorySegment FromAsciiz(TChar * Asciiz);
    TMemorySegment FromAsciiz(const TChar * Asciiz); // <3 U C

    // Return true if segments intersect
    TBool Intersects(TMemorySegment A, TMemorySegment B);

    // Compare for equality
    TBool AreEqual(TMemorySegment A, TMemorySegment B);
  }
}

/*
  2024-05-17
  2024-05-23 GetByte
  2024-05-25 PrintWrappings, PrintMem, CopyMemTo, Spawn, Kill
  2024-05-27 ReserveChunk, ReleaseChunk, ZeroMem
  2024-05-30 CloneFrom
  2024-06-02 < CloneFrom
  2024-06-04
  2024-06-07 IsEqualTo
  2024-06-08 IsEqualTo.Asciiz
  2024-09-15 Zeroing before alloc/free is part of contract now
  2024-10-05 Freetown. Moved memory-changing code to [me_ManagedMemory]
*/
