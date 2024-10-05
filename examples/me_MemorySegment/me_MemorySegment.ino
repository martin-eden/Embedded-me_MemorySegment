// [me_MemorySegment] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-10-05
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
  RunTest();
  printf("[me_MemorySegment] Done.\n");
}

void loop()
{
}

// --

void RunTest()
{
  printf(
    "This demo will show typical applications of [me_MemorySegment].\n"
    "We recommend to match output with reading code.\n"
    "\n"
  );

  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::Print,
    me_MemorySegment::Freetown::PrintWrappings;

  TMemorySegment MemSeg;

  printf("Casting ASCIIZ to memory segment:\n");

  // Treat ASCIIZ as memory segment. Just cast, no data copied.
  MemSeg = FromAsciiz("ASCIIZ as memory segment. Goodbye zero tail!");

  printf("Contents( ");
  Print(MemSeg);
  printf(" )\n");
  printf("\n");

  printf("Casting AVR registers to memory segment:\n");

  // AVR registers are at addresses 0 .. 31
  MemSeg.Start.Addr = 0;
  MemSeg.Size = 32;

  printf("Debug contents(\n");
  PrintWrappings(&MemSeg);
  printf(")\n");
  printf("\n");

  printf(
    ".. also there are intersection and equality checking functions.\n"
    "But we are too lazy to write demo code for them.\n"
    "\n"
  );
}

/*
  2024-05-17
  2024-05-25
  2024-05-27
  2024-05-29
  2024-06-02
  2024-10-05
*/
