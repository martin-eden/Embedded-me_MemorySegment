// [me_MemorySegment] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-06-02
*/

#include <me_MemorySegment.h>

#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>
#include <me_BaseTypes.h>

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  InstallStandardStreams();

  printf("[me_MemorySegment] Okay, we are here.\n");
  Test();
  printf("Done.\n");
}

void loop()
{
}

void Test()
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::FromAsciiz;

  TMemorySegment MemSeg;

  // Treat ASCIIZ as memory segment. Just cast, no data copied.
  MemSeg = FromAsciiz("ASCIIZ as memory segment. Goodbye strlen()!");

  printf("Casting memory segment to ASCIIZ:\n");
  PrintSegment(&MemSeg);

  // Describe some arbitrary memory segment.
  // AVR registers are at addresses 0 .. 31
  MemSeg.Start.Addr = 0;
  MemSeg.Size = 32;

  printf("Casting memory segment to AVR registers:\n");
  PrintSegment(&MemSeg);
}

void PrintSegment(me_MemorySegment::TMemorySegment * MemSeg)
{
  // Print range
  printf("Segment( ");
  MemSeg->PrintWrappings();
  printf(" )\n");

  // Print contents
  printf("Contents( ");
  MemSeg->Print();
  printf(" )\n");

  printf("\n");
}

/*
  2024-05-17
  2024-05-25
  2024-05-27
  2024-05-29
  2024-06-02
*/
