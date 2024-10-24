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
    TUint_2 Addr = 0;
    // "Bytes" provides array access to memory at "Start.Addr"
    TUint_1 * Bytes;
  };
  TUint_2 Size = 0;
};
```

This structure is our type for variable-length data in RAM.

### `.Bytes`

`Bytes` field is a sort of compiler's hack. It tells compiler that
given address is pointer to byte. And C++ is always happy to treat
anything as array.

For example let's divide value in register R3 by 2 (just for example):

```C++
TMemorySegment Registers;
Resisters.Addr = 0;
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
  This demo will show typical applications of [me_MemorySegment].

  Module provides functions to cast memory segment from ASCIIZ.
  Plus debug print.

  Also there are intersection and equality checking functions.
  But we are too lazy to write demo code for them.

  We recommend to match output with reading code.
    --
    ASCIIZ to memory segment
      Contents ( Goodbye zero tail! )
      Debug contents (
        TMemorySegment (
          Addr 00682
          Size 00018
          Data ( 071 111 111 100 098 121 101 032 122 101 114 111 032 116 097 105 108 033 )
        )
      )
    --
    AVR registers to memory segment
      Debug contents (
        TMemorySegment (
          Addr 00000
          Size 00032
          Data ( 163 000 000 000 174 008 003 000 001 001 032 000 000 000 232 008 016 000 000 000 000 000 048 008 002 000 003 000 231 008 030 000 )
        )
      )
    --
  --
[me_MemorySegment] Done.

```

## Code

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]
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
[Implementation]: src/me_MemorySegment.cpp
[Design notes]: extras/Design%20notes.txt

[me_ManagedMemory]: https://github.com/martin-eden/Embedded-me_ManagedMemory
[me_List]: https://github.com/martin-eden/Embedded-me_List
[me_Menu]: https://github.com/martin-eden/Embedded-me_Menu
[me_RgbStripeConsole]: https://github.com/martin-eden/Embedded-me_RgbStripeConsole

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
