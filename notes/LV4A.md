# LV4A - Basic Instructions - Overview
---
## Overview
- Overview
- Copying data
- Integer addition and subtraction instructions
- Multiplication instructions
- Division instructions
---
## 80x86 Instructions categories
- Data movement instructions
  - mov lea les push pop pushf popf
- Conversions
  - cbw cwd xlat
- Arithmetic instructons
  - add inc sub cmp neg mul imul div idiv
- Logical shift rotate and bit instructions
  - and or xor not shl shr rcl rcr
- I/O instructions
  - in out
- String instructions
  - movs stos lods
- Program flow control instructions
  - jmp call ret j*(conditional jmp)
- Miscellaneous instructions
  - clc stc cmc
---
## Assembly to machine code
- Object code for assembly instruction
  - hex encoded
  - <opcode> [<operand1>, <operand2>, ...]
  - {mnemonic, operands} => hex opcode
    - mnemonic => name of instruction ie. mov
  - operand(s) => hex encoded
- Addressing modes
  - immediate, data located in instruction
  - register, data located in register specified
  - memory
    - direct, data located at the memory address specified
    - indirect, data located behind "pointer" at the memory address specified
---
## Mnemonic to Opcode
- One mnemonic can generate multiple opcodes
  - depends on addressing mode of operands
- Opcode chosen by assembler
  - mov eax, number => A1
  - mov sum, eax => A3
  - mov eax, 0 => B8
---
## Machine/object code generation
- R => relocatable address, address will be different at runtime
---
## Flags register
- Maintains the current operating state of the CPU
- And some instruction state information
---
