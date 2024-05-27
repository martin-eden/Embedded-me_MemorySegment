// ReserveChunk()/ReleaseChunk() for TMemorySegment

/*
  We can pretend we _manage_ memory we are describing.

  Under "manage" I mean we call "malloc(self.Size)" when you want us
  to allocate memory. And we call "free(self.Addr)" when you want us
  to release it. These actions will modify our fields.

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
  if (this->Start.Addr != 0)
    return false;

  if (this->Size == 0)
    return false;

  TUint_2 Addr = (TUint_2) malloc(this->Size);

  if (Addr == 0)
    return false;

  this->Start.Addr = Addr;

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
  if (this->Start.Addr == 0)
    return false;

  if (this->Size == 0)
    return false;

  free((void *) this->Start.Addr);

  this->Start.Addr = 0;
  this->Size = 0;

  return true;
}

/*
  2024-05-27
*/
