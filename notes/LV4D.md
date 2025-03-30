# LV4D - Basic Instructions - Copying `Word` `Dword` `Qword`
---
## Machine Code - Move a `word`
Move a `word` has a 66| opcode prefix for 32-bit mode.

For 64-bit mode had 66| opcode prefix and `rex` 4x/ prefix
---
## Machine Code - Move a `dword`
Move a `dword` has a no prefix in 32-bit mode.

For 64-bit mode has 4x/ `rex` prefix
---
## Machine code - Move a `qword`
64-bit only.

Move a `qword` has a `rex` 4x/ opcode prefix
---
## XCHG Pneumonic
`xchg <op1> <op2>`
- Swaps the values referenced by its two operands
  - both cannot be in memory
- Affects no flags

```asm
mov ecx, eax
mov eax, ebx
mov ebx, ecx
```
or 
```asm
xchg eax, ebx
```
can be:
  - xchg reg, mem
  - xchg reg, reg
  - xchg ax, reg16
  - xchg eax, reg32
---
