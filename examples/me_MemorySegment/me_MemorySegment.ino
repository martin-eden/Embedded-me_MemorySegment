// [me_MemorySegment] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-10-08
*/

#include <me_MemorySegment.h>

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_Console.h>

void setup()
{
  Console.Init(me_UartSpeeds::Arduino_Normal_Bps);

  Console.Print("[me_MemorySegment] Okay, we are here.");
  RunTest();
  Console.Print("[me_MemorySegment] Done.");
}

void loop()
{
}

// --

void RunTest()
{
  /*
    Guys, sorry for example cluttered with pretty-printing.
  */

  Console.Line();
  Console.Write(
    "This demo will show typical applications of [me_MemorySegment]\n"
    "We recommend to match output with reading code.\n"
  );
  Console.Indent();

  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::PrintWrappings;

  TMemorySegment MemSeg;

  Console.Print("Getting memory segment from ASCIIZ");

  // Treat ASCIIZ as memory segment. Just cast, no data copied.
  MemSeg = FromAsciiz("ASCIIZ as memory segment. Goodbye zero tail!");

  Console.Indent();
  Console.Write("Contents ( ");
  Console.Write(MemSeg);
  Console.Write(" )");
  Console.Newline();
  Console.Unindent();

  Console.Indent();
  Console.Write("Debug contents ( ");
  Console.Indent();
  PrintWrappings(MemSeg);
  Console.Unindent();
  Console.Write(")");
  Console.Newline();
  Console.Unindent();

  Console.Line();

  Console.Print("Getting memory segment from AVR registers");

  // AVR registers are at addresses 0 .. 31
  MemSeg.Start.Addr = 0;
  MemSeg.Size = 32;

  Console.Indent();
  Console.Write("Debug contents ( ");
  Console.Indent();
  PrintWrappings(MemSeg);
  Console.Unindent();
  Console.Write(")");
  Console.Newline();
  Console.Unindent();

  Console.Unindent();

  Console.Write(
    "\n"
    ".. also there are intersection and equality checking functions.\n"
    "But we are too lazy to write demo code for them.\n"
  );
  Console.Line();
}

/*
  2024-05-17
  2024-05-25
  2024-05-27
  2024-05-29
  2024-06-02
  2024-10-05
  2024-10-08
*/
