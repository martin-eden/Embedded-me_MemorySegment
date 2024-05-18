// [me_MemorySegment] compilation test

/*
  Author: Martin Eden
  Last mod.: 2024-05-17
*/

#include <me_MemorySegment.h>

void setup()
{
  using namespace me_MemorySegment;

  TMemorySegment RegsSpan =
    { .Start = 0x00, .Size = 0x20 };

  TMemorySegment_Bits CompareModeChB =
    {
      .Start = { .Base = 0x44, .BitOffs = 5 },
      .Size = 2,
    };
}

void loop()
{
}

/*
  2024-05-17
*/
