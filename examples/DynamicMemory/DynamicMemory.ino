// [me_MemorySegment] (Reserve/Release)Chunk() test

/*
  Author: Martin Eden
  Last mod.: 2024-06-01
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
  me_BaseTypes::TUint_1,
  me_BaseTypes::TUint_2;

void Test()
{
  using me_MemorySegment::TMemorySegment;

  {
    printf("One memory segment reserve/release:\n");

    /*
      Address of segment must be 0 when we call ReserveChunk()

      TMemorySegment has a zeroing constructor. So we just need to set
      <.Size> before ReserveChunk().
    */
    TMemorySegment Seg;
    TUint_2 SegSize = 16;

    VerboseReserve(&Seg, SegSize);
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
      if (!VerboseReserve(&Segments[NumAllocated], ChunkSize))
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
  me_MemorySegment::TMemorySegment * MemSeg,
  me_BaseTypes::TUint_2 SegSize
)
{
  MemSeg->PrintWrappings();
  printf(" -> ");

  if (!MemSeg->Reserve(SegSize))
  {
    printf("Reserve() failed.\n");
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

  if (!MemSeg->Release())
  {
    printf("Release() failed.\n");
    MemSeg->PrintWrappings();
    return false;
  }
  printf("Released.");
  MemSeg->PrintWrappings();
  printf("\n");

  return true;
}

/*
  2024-05-27
  2024-06-02
*/
