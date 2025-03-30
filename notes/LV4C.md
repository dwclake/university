# LV4C - Basic Instructions - Mod R/M and Rex Prefix
---
## Reg 8/ Memory -> Reg 8
- Opcode is 8A, extra byte needed to specify destination and source
- Destination always a reg 8
---
## Mod R/M Byte
- Opcode B0..B8 -> Immediate addressing, opcode indicates destination
- Opcode 8A -> Reg to reg
  - Instructions obj code looks like 8A__
  - 64 combinations
    - 8 sources
    - 8 destinations
  - Second byte encodes destination and source -> Mod R/M
---
## Mod Reg R/M Fields
- mod (mode), 2 bits
- reg (register), 3 bits
- r/m (register/memory), 3 bits
- 0b mod, reg, r/m
  - example mod of 11 means both operands are registers
---
## Mod
- 00: Memory addressing, direct/indirect
- 01: Not covered
- 10: Not covered
- 11: Register addressing mode
---
## R/M Fields
- 000 AL AX EAX
- 001 CL CX ECX
- 010 DL DX EDX
- 011 BL BX EBX
- 100 AH SP ESP
- 101 CH BP EBP
- 110 DH SI ESI
- 111 BH DI EDI
---
## R/M when mod is 00, Memory Addressing
- If memory direct, 2 (op) + 4 (address) bytes, R/M is 101
- If memory indirect, 2 (op) bytes, register encoded in R/M contains address to source
---
## Other opcodes with Mod R/M
- C6, 88
---
## 64-bit Mode
- 16 general purpose registers
- Default address size is 64 bits, and operand size is 32 bit
- Memory Addressing is done as a 32-bit offset of RIP
- GP registers are able to work with either 32-bit or 64-bit operands
  - For 32-bit operand: EAX, EBX, ECX, EDX, EDI, ESI, EBP, ESP, R8D - R15D
  - For 64-bit operand: RAX, RBX, RCX, RDI, RSI, RBP, RSP, R8-R15
  - All of these registers support byte, word, dword, and qword levels
- 64 bit instructions are similar to 32 bit instructions
  - REX prefixes are used to generate 64-bit operand sizes or to reference registers R8-R15
  - The extra byte in Opcode
  - First 4 bits are always 0100 0x4 (from left to right)
  - Zeroth bit is used with R/M to support 16 registers B
  - Second bit is used with Reg to support 16 registers R
  - Placed before opcode with /, i.e: 45/ 8A C6 -> mov R8B, R14B
---
## REX Prefix
- 0100WRXB
- W - 1 if 64-bit operand
- R - Extends Mod R/M reg field
- X - Extends SIB index
- B - Extends Mod R/M r/m field
- SIB Byte - used to cover special cases of addressing
---
