# What

(2024-05 .. 2024-06, 2024-09)

Arduino library to work with memory segment.


## Design

Okay, we have state -- description of segment in memory.
We describe it by starting address and size.

Then we have core functions: zero, copy and compare.

Plus we have dynamic memory allocation and deallocation (Reserve() and
Release()).

Memory allocation guarantees that data at memory are zeroed and
deallocator zeroes memory before release.

Reserve() and Release() are idempotent: you can call them as many
times as you please. Only first call will matter.

Interface also adds some quality-of-life functions like printing
state, printing data and converting ASCIIZ (aka "C string") to state.


## Interface

  * State

    ```C++
    union
    {
      TMemoryPoint Start = { .Addr = 0 };
      TUint_1 * Bytes;
    };
    TUint_2 Size = 0;
    ```

    That's out state. Block of memory at address (`TUint_2 Start.Addr`)
    with known size (`TUnt_2 Size`). Also we have convenient byte access
    to data at that address (`TUint_1 * Bytes`).

    * Zero: Fill memory with zeroes

      ```C
      void ZeroMem();
      ```
    * Copy

      * Copy memory to another segment

        ```C
        TBool CopyMemTo(TMemorySegment Dest);
        ```

      * Copy memory from another segment

        ```C
        TBool CopyMemFrom(TMemorySegment Src);
        ```

    * Compare

      * Compare for equality

        ```C
        TBool IsEqualTo(TMemorySegment Another);
        ```

      * Compare for equality with ASCIIZ

        ```C
        TBool IsEqualTo(const TChar * Asciiz);
        ```

    * Reserve block of memory and zero it

      ```C
      TBool Reserve(TUint_2 SegSize);
      ```

    * Release block of memory and zero it before

      ```C
      TBool Release();
      ```

    * Print state to stdout

      ```C
      void PrintWrappings();
      ```

    * Print raw bytes of memory segment to stdout

      ```C
      void Print();
      ```

    * Treat ASCIIZ as state

      ```C
      // Describe ASCIIZ structure as memory segment
      TMemorySegment FromAsciiz(TChar * Asciiz);
      TMemorySegment FromAsciiz(const TChar * Asciiz); // <3 U C
      ```

## Code

* [Example](examples/me_MemorySegment/me_MemorySegment.ino)
* [Interface](src/me_MemorySegment.h)
* [Implementation](src/me_MemorySegment.cpp)
* [Design notes](extras/Design%20notes.txt)


## Requirements

  * arduino-cli
  * bash


## Install

Run [Install.sh](Install.sh).


## Remove

Run [Remove.sh](Remove.sh).


## See also

* [My other embedded C++ libraries](https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts)
* [My other repositories](https://github.com/martin-eden/contents)
