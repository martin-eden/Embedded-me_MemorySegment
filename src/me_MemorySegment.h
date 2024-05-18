// Memory segment structure

/*
  Author: Martin Eden
  Last mod.: 2024-05-18
*/

// Data structures is the base. Algorithms just spawn on them like plant species.

#pragma once

#include <me_MemoryPoint.h>
#include <me_BaseTypes.h>

namespace me_MemorySegment
{
  using namespace me_MemoryPoint;
  using namespace me_BaseTypes;

  /*
    Memory span with byte granularity
  */
  struct TMemorySegment
  {
    TMemoryPoint Start;
    TUint_2 Size;
  };

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
*/
