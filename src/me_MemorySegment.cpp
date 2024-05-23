// Memory segment companion functions

/*
  Author: Martin Eden
  Last mod.: 2024-05-23
*/

#include "me_MemorySegment.h"

#include <me_BaseTypes.h>

using namespace me_BaseTypes;

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
  2024-05-23 GetByte
*/
