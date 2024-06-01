// [me_MemorySegment] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-06-01
*/

#include <me_MemorySegment.h>
#include <me_BaseTypes.h>

#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>

// Forwards:
void Test();

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  InstallStandardStreams();

  printf("[me_MemorySegment] Okay, we are here.\n");

  Test();
}

void loop()
{
}

void Test()
{
  using
    me_BaseTypes::TChar,
    me_BaseTypes::TUint_2,
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::FromAsciiz,
    me_MemorySegment::Spawn,
    me_MemorySegment::Kill;

  // Treat ASCIIZ as memory segment. No data copied.
  TMemorySegment MessageSeg = FromAsciiz((TChar *)"Spawn Copy Kill");

  // Print range
  printf("Message-Segment( ");
  MessageSeg.PrintWrappings();
  printf(" )\n");

  // Print contents
  printf("Message-Mem( ");
  MessageSeg.Print();
  printf(" )\n");

  /*
    Now the harder part. Heap memory.

    We will create copy of <MessageSeg> in heap. Then will free it.

    Creating a copy is common functionality over .ReserveChunk() and
    .CopyMemFrom(). It is implemented in .CloneFrom().
  */
  TMemorySegment * MessageSeg_Copy;

  // Allocate node
  if (!Spawn(&MessageSeg_Copy))
  {
    printf("Failed to spawn memory segment record.\n");
    return;
  }
  printf("Spawned at [0x%04X].\n", (TUint_2) MessageSeg_Copy);

  if (!MessageSeg_Copy->CloneFrom(&MessageSeg))
  {
    printf("Failed to clone segment. Probably, no memory.\n");
    Kill(MessageSeg_Copy);
  }

  printf("MessageSeg_Copy-Segment( ");
  MessageSeg_Copy->PrintWrappings();
  printf(" )\n");

  printf("MessageSeg_Copy-Mem( ");
  MessageSeg_Copy->Print();
  printf(" )\n");

  // Free data
  if (!MessageSeg_Copy->ReleaseChunk())
  {
    printf("Failed to release chunk.\n");
    Kill(MessageSeg_Copy);
    return;
  }
  printf("Freed data memory.\n");

  // Free node
  if (!Kill(MessageSeg_Copy))
  {
    printf("Failed to kill memory segment.\n");
    return;
  }
  printf("Killed [0x%04X].\n", (TUint_2) MessageSeg_Copy);
}

/*
  2024-05-17
  2024-05-25
  2024-05-27
  2024-05-29
*/
