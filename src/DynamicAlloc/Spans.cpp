// ReserveChunk()/ReleaseChunk() for TMemorySegment

/*
  We can pretend we _manage_ memory we are describing.

  Under "manage" I mean we call "malloc(self.Size)" when you want us
  to allocate memory. And we call "free(self.Addr)" when you want us
  to release it. These actions will modify our fields.

  Memory span is zeroed after allocation. Memory span is zeroed
  before release.

  Reserve memory block of <.Size>:

    bool .Reserve()

    Before: <.Start.Addr> = 0
    After: <.Start.Addr> != 0

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
  Last mod.: 2024-05-27
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

  ASSERT YEP <.Start.Addr> = 0 // That's for safety.
  ASSERT NAH <.Size> = 0 // That's for sanity.

  After malloc():

    <.Start.Addr> = Addr
*/
TBool TMemorySegment::ReserveChunk()
{
  if (Start.Addr != 0)
    return false;

  if (Size == 0)
    return false;

  TUint_2 MallocAddr = (TUint_2) malloc(Size);

  if (MallocAddr == 0)
    return false;

  Start.Addr = MallocAddr;

  ZeroMem();

  return true;
}

/*
  Release block of memory

  Implemented as wrapper over free().

  ASSERT NAH <.Start.Addr> = 0 // That's for safety.
  ASSERT NAH <.Size> = 0 // That's for sanity.

  After free():

    <.Start.Addr> = 0
    <.Size> = 0
*/
TBool TMemorySegment::ReleaseChunk()
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
*/
