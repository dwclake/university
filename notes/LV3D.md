# LV3D - Elements of Assembly Language - Instruction Operands
---
## Addressing
Immediate mode:
  - Constant assembled into the instruction
Register mode:
  - A code for the register is assembled into the instruction
Memory References:
  - A address to memory is assembled into the instruction

Mnemonics:
  - inc EAX ; increment and assign EAX (register)
  - dec number1 ; decrement and assign number1 (memory (direct))
  - add, mov, sub
---
## Memory References
Direct:
  - At a memory location whose address is built into the instruction
  - 'Pass by value'
Indirect:
  - At a memory location whose address is in a register
  - 'Pointer/Pass by reference'
  - mov DWORD PTR [ebx], 10
    - move 10 into the address stored in ebx
---
