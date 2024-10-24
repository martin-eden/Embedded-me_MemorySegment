// [me_MemorySegment] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-10-24
*/

#include <me_MemorySegment.h>

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_Console.h>

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);

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

    This sketch also serves as field test of [me_Conosle].
  */
  Console.Indent();

  Console.Print("--");
  Console.Print("This demo will show typical applications of [me_MemorySegment].");
  Console.Print("");
  Console.Print("Module provides functions to cast memory segment from ASCIIZ.");
  Console.Print("Plus debug print.");
  Console.Print("");
  Console.Print("Also there are intersection and equality checking functions.");
  Console.Print("But we are too lazy to write demo code for them.");
  Console.Print("");
  Console.Print("We recommend to match output with reading code.");

  Console.Indent();

  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::PrintWrappings;

  TMemorySegment MemSeg;

  Console.Print("--");
  Console.Print("ASCIIZ to memory segment");

  // Treat ASCIIZ as memory segment. Just cast, no data copied.
  MemSeg = FromAsciiz("Goodbye zero tail!");

  Console.Indent();
  Console.Write("Contents ( ");
  Console.Write(MemSeg);
  Console.Write(" )");
  Console.EndLine();
  Console.Unindent();

  Console.Indent();
  Console.Write("Debug contents (");
  Console.Indent();
  PrintWrappings(MemSeg);
  Console.Unindent();
  Console.Write(")");
  Console.EndLine();
  Console.Unindent();

  Console.Print("--");

  Console.Print("AVR registers to memory segment");

  // AVR registers are at addresses 0 .. 31
  MemSeg.Addr = 0;
  MemSeg.Size = 32;

  Console.Indent();
  Console.Write("Debug contents (");
  Console.Indent();
  PrintWrappings(MemSeg);
  Console.Unindent();
  Console.Write(")");
  Console.EndLine();
  Console.Unindent();

  Console.Print("--");
  Console.Unindent();

  Console.Print("--");
  Console.Unindent();
}

/*
  2024-05-17
  2024-05-25
  2024-05-27
  2024-05-29
  2024-06-02
  2024-10-05
  2024-10-08
  2024-10-10
  2024-10-18
*/
