// [me_MemorySegment] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-05-25
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
    me_BaseTypes::TUint_2,
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::FromAsciiz,
    me_MemorySegment::Spawn,
    me_MemorySegment::Kill;

  // Load from ASCIIZ
  TMemorySegment Message = FromAsciiz("Spawn Copy Kill");

  // Print range
  printf("Message-Segment( ");
  Message.PrintWrappings();
  printf(" )\n");

  // Print contents
  printf("Message-Mem( ");
  Message.PrintMem();
  printf(" )\n");

  /*
    Now the hard part. Heap memory.

    We will create copy of <Message> in heap. Then will free it.
  */
  TMemorySegment * Message_Copy;

  // Allocate node
  if (!Spawn(&Message_Copy))
  {
    printf("Failed to spawn memory segment record.\n");
    return;
  }
  printf("Spawned at [0x%04X].\n", (TUint_2) Message_Copy);

  // Allocate mem for data
  TUint_2 CharsCopyStorageAddr = (TUint_2) malloc(Message.Size);
  if (CharsCopyStorageAddr == 0)
  {
    printf("No mem for data copy.\n");
    Kill(Message_Copy);
    return;
  }
  printf("Allocated memory for copy at [0x%04X].\n", CharsCopyStorageAddr);

  // Setup node
  Message_Copy->Start.Addr = CharsCopyStorageAddr;
  Message_Copy->Size = Message.Size;

  // Copy data
  Message.CopyMemTo(*Message_Copy);

  printf("Message_Copy-Segment( ");
  Message_Copy->PrintWrappings();
  printf(" )\n");

  printf("Message_Copy-Mem( ");
  Message_Copy->PrintMem();
  printf(" )\n");

  // Free data
  free((void *) Message_Copy->Start.Addr);
  printf("Freed data memory at [0x%04X].\n", Message_Copy->Start.Addr);

  // Free node
  if (!Kill(Message_Copy))
  {
    printf("Failed to kill memory segment.\n");
    return;
  }
  printf("Killed [0x%04X].\n", (TUint_2) Message_Copy);
}

/*
  2024-05-17
  2024-05-25
*/
