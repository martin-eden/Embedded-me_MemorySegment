# What

(2024-05/2024-06, 2024-09/2024-10)

Arduino library describing memory segment.


## Design

Memory segment is a range of memory addresses.

```C++
struct TMemorySegment
{
  union
  {
    TMemoryPoint Start = { .Addr = 0 };
    // "Bytes" provides array access to memory at "Start.Addr"
    TUint_1 * Bytes;
  };
  TUint_2 Size = 0;
}
```

This structure is our type for variable-length data in RAM.

### `.Bytes`

`Bytes` field is a sort of compiler's hack. It tells compiler that
given address is pointer to byte. And C++ is always happy to treat
anything as array.

For example let's divide value in register R3 by 2 (just for example):

```C++
TMemorySegment Registers;
Resisters.Start.Addr = 0;
Registers.Size = 32;

Registers.Bytes[3] = Registers.Bytes[3] / 2;
```

This works while segment describes span in RAM. (Not in flash or in EEPROM
for example.)


## Uses

Actually this module became like new base type and widely used
by my other libraries.


## Sample output

```
[me_MemorySegment] Okay, we are here.
--
This demo will show typical applications of [me_MemorySegment]
We recommend to match output with reading code.

  Getting memory segment from ASCIIZ
    Contents ( ASCIIZ as memory segment. Goodbye zero tail! )
    Debug contents (
      TMemorySegment
      (
        Start 00513
        Size 00044
        Data ( 065 083 067 073 073 090 032 097 115 032 109 101 109 111 114 121 032 115 101 103 109 101 110 116 046 032 071 111 111 100 098 121 101 032 122 101 114 111 032 116 097 105 108 033 )
      )
    )
  --
  Getting memory segment from AVR registers
    Debug contents (
      TMemorySegment
      (
        Start 00000
        Size 00032
        Data ( 128 000 255 003 010 000 000 000 000 000 032 032 032 000 000 000 016 000 206 003 001 000 000 000 001 003 236 008 235 008 030 000 )
      )
    )

.. also there are intersection and equality checking functions.
But we are too lazy to write demo code for them.

--
[me_MemorySegment] Done.
```

## Code

* [Example][Example]
* [Interface][Interface]
* Implementation
  * [Free functions][Freetown]
* [Design notes][Design notes]


## Requirements

  * arduino-cli
  * bash


## Install

Run [Install.sh](Install.sh).


## Remove

Run [Remove.sh](Remove.sh).


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[Example]: examples/me_MemorySegment/me_MemorySegment.ino
[Interface]: src/me_MemorySegment.h
[Freetown]: src/me_MemorySegment_Freetown.cpp
[Design notes]: extras/Design%20notes.txt

[me_ManagedMemory]: https://github.com/martin-eden/Embedded-me_ManagedMemory
[me_List]: https://github.com/martin-eden/Embedded-me_List
[me_Menu]: https://github.com/martin-eden/Embedded-me_Menu
[me_RgbStripeConsole]: https://github.com/martin-eden/Embedded-me_RgbStripeConsole

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
