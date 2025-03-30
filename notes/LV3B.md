# LV3B - Elements of Assembly Language - 32-bit Example
---
## Outputs of Assembler
- Object file .obj
  - Machine language statements almost ready to execute
- Listing file .lst
  - Shows how the assembler translated the source program
---
## Parts of an instruction
Instructions object code begins with the opcode, usually one byte
  - A1 for mov eax, number 
Immediate operands are constants embedded in the object code
  - Example, 0000009E for add eax, 158
  - Addresses are assembly-time; must be fixed when program is linked and loaded
---