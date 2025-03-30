# LV4E - Basic Instructions - Integer Addition and Subtraction
---
## Basic Instructions
- Add
- Sub
- Inc
- Dec
- Neg
---
## Flags Register
bits:
  - 0: CF Carry Flag
  - 1: Reserved
  - 2: PF Parity Flag
  - 3: Reserved
  - 4: AF Adjust Flag
  - 5: Reserved
  - 6: ZF Zero Flag
  - 7: SF Sign Flag
  - 8: TF Trap Flag
  - 9: IF Interrupt enable Flag
  - 10: DF Direction Flag
  - 11: OF Overflow Flag
  - 12-13: IOPL I/O Privlage Level
  - 14: NT Nested task Flag
  - 15: Reserved
---
## EFlags and RFLags Register
bits:
  - 16: RF Resume Flag
  - 17: VM Virtual 8086 mode Flag
  - 18: AC Alignment Check
  - 19: VIF Virtual interrupt Flag
  - 20: VIP Virtual interrupt pending Flag
  - 21: ID Able to use CPUID instruction
  - 22-63: RFlags Reserved
---
## ADD Instruction
Format: add destination, source

The integer at source is added to the integer at destination and the sum replaces the old
value at destination

source content is not altered

`Flags altered`: SF ZF OF CF PF AF depending on result of operation
---
## Addition Example
```asm
Before:
  EAX: 00000075
  ECX: 000001A2

Instruction:
  add eax, ecx

After:
  EAX: 00000217
  ECX: 000001A2
  SF=0 ZF=0 CF=0 OF=0
```
---
## SUB Instruction
Format: sub destination, source

The integer at source is subtracted from the integer at destination
and the difference replaces the old value at destination

Source content is not altered

`Flags altered`: SF ZF OF CF PF AF depending on result of the operation
---
## Subtraction Example
```asm
Before:
  doubleword at Dbl: 00000100
Instruction:
  sub Dbl, 2

After:
  Dbl: 000000FE
  SF=0 ZF=0 CF=0 OF=0
```
---