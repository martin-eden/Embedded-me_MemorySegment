// [me_MemorySegment] (Reserve/Release)Chunk() test

/*
  Author: Martin Eden
  Last mod.: 2024-05-29
*/

#include <me_MemorySegment.h>

#include <me_InstallStandardStreams.h>
#include <me_UartSpeeds.h>
#include <me_BaseTypes.h>

// Forwards:
void Test();

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  InstallStandardStreams();

  printf("[me_MemorySegment.DynamicMemory] Okay, we are here.\n");

  Test();

  printf("Done.\n.\n");
}

void loop()
{
}

using
  me_BaseTypes::TBool,
  me_BaseTypes::TUint_1;

// Forwards:
TBool VerboseReserve(me_MemorySegment::TMemorySegment * MemSeg);
TBool VerboseRelease(me_MemorySegment::TMemorySegment * MemSeg);

void Test()
{
  using me_MemorySegment::TMemorySegment;

  {
    printf("One memory segment reserve/release:\n");

    // Address of segment must be 0 when we call Reserve()

    // note (1)
    TMemorySegment Seg = { { 0 }, .Size = 16 };

    VerboseReserve(&Seg);
    VerboseRelease(&Seg);

    printf("--\n");
  }

  {
    printf("Several segments reserve/release:\n");

    const TUint_1 NumSegments = 3;
    TMemorySegment Segments[NumSegments];

    // Allocate several memory chunks:
    const TUint_1 ChunkSize = 14;
    for (TUint_1 NumAllocated = 0; NumAllocated < NumSegments; ++NumAllocated)
    {
      TMemorySegment * CurSegment = &(Segments[NumAllocated]);

      CurSegment->Start.Addr = 0;
      CurSegment->Size = ChunkSize;

      if (!VerboseReserve(&Segments[NumAllocated]))
        return;
    }

    // Release them
    for (TUint_1 NumReleased = 0; NumReleased < NumSegments; ++NumReleased)
    {
      if (!VerboseRelease(&Segments[NumReleased]))
        return;
    }

    printf("--\n");
  }
}

me_BaseTypes::TBool VerboseReserve(
  me_MemorySegment::TMemorySegment * MemSeg
)
{
  MemSeg->PrintWrappings();
  printf(" -> ");

  if (!MemSeg->ReserveChunk())
  {
    printf("ReserveChunk() failed.\n");
    MemSeg->PrintWrappings();
    return false;
  }
  printf("Reserved.");
  MemSeg->PrintWrappings();
  printf("\n");

  return true;
}

me_BaseTypes::TBool VerboseRelease(
  me_MemorySegment::TMemorySegment * MemSeg
)
{
  MemSeg->PrintWrappings();
  printf(" -> ");

  if (!MemSeg->ReleaseChunk())
  {
    printf("ReleaseChunk() failed.\n");
    MemSeg->PrintWrappings();
    return false;
  }
  printf("Released.");
  MemSeg->PrintWrappings();
  printf("\n");

  return true;
}

/*
  [1]:

    First element of structure is anonymous union.

    I would like to initialize it by specifying member like

      TMemorySegment Seg = { .Start = { .Addr = 0 }, .Size = 16 };

    But compiler gives me

      sorry, unimplemented: non-trivial designated initializers not supported

    So reverted to

      TMemorySegment Seg = { { 0 }, .Size = 16 };
*/

/*
  2024-05-27
*/
