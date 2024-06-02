// ReserveChunk()/ReleaseChunk() for TMemorySegment

/*
  We can pretend we _manage_ memory we are describing.

  Under "manage" I mean we call "malloc(self.Size)" when you want us
  to allocate memory. And we call "free(self.Addr)" when you want us
  to release it. These actions will modify our fields.

  Memory span is zeroed after allocation. Memory span is zeroed
  before release.

  Reserve memory block of <Size> bytes:

    bool .Reserve(<Size>)

    Before:
      <.Start.Addr> = 0
      <.Size> = 0
    After:
      <.Start.Addr> != 0
      <.Size> = <Size>

  Free memory block by address <.Start.Addr>:

    bool .Release()

    Before:
      <.Start.Addr> != 0
      <.Size> != 0
    After:
      <.Start.Addr> = 0
      <.Size> = 0
*/

/*
  Author: Martin Eden
  Last mod.: 2024-06-02
*/

#include "me_MemorySegment.h"

#include <stdlib.h> // malloc(), free()

#include <me_BaseTypes.h>

using
  me_BaseTypes::TUint_2,
  me_BaseTypes::TBool,
  me_MemorySegment::TMemorySegment;

/*
  Reserve block of memory

  Implemented as wrapper over malloc().

  Before:

    <.Start.Addr> = 0
    <.Size> = 0
    <SegSize> != 0

  After:

    <.Start.Addr> = ...
    <.Size> = <SegSize>
*/
TBool TMemorySegment::Reserve(TUint_2 SegSize)
{
  if (Start.Addr != 0)
    return false;

  if (Size != 0)
    return false;

  if (SegSize == 0)
    return false;

  TUint_2 MallocAddr = (TUint_2) malloc(SegSize);

  if (MallocAddr == 0)
    return false;

  Start.Addr = MallocAddr;
  Size = SegSize;

  ZeroMem();

  return true;
}

/*
  Release block of memory

  Implemented as wrapper over free().

  Before:

    <.Start.Addr> != 0
    <.Size> != 0

  After:

    <.Start.Addr> = 0
    <.Size> = 0
*/
TBool TMemorySegment::Release()
{
  if (Start.Addr == 0)
    return false;

  if (Size == 0)
    return false;

  ZeroMem();

  free((void *) Start.Addr);

  Start.Addr = 0;
  Size = 0;

  return true;
}

/*
  2024-05-27
  2024-06-02
*/
