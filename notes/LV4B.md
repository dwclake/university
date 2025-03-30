# LV4B - Basic Instructions - Copying Byte
---
## Mov instruction

mov instructions are really copy instructions, like simple assignment statements in a 
high level language.

format:
  - mov destination, source
  - mneumonic operand1, operand2
  - destination can be register or memory
  - source can be register, memory, or immediate
---
## Effect on Flags

In general, an instruction may have one or three effects:
  - No flags altered
  - Specific flags are given values depending on result of instruction
  - Some flags may be altered, but there settings cannot be predicted
mov instructions never change any flag
---
## Operand restrictions
- Operands must be the same sizes
- Cannot move from memory to memory
  - must use register as intermediate storage
- Can only move one byte, word, or double word at a time
- mov destination, source
- several different opcodes
- Depends on type(s) of destination and source
---
## Machine code
- Depends on operand type(s), with several different opcodes used for mov instructions
- Word-size and double word-size instructions use same opcodes, but word-size instructions have 0x66 prefix byte
- Object code ~ Machine code
- Word sized operations prefixed with 66
- R -> relocatable memory address, ie placeholder address, will be whatever address is assigned
to that data variable at runtime
```
B0 9B       mov al, 155
66| B8 009B mov ax, 155
B8 0000009B mov eax, 155
```
---
## Move a byte
<pre>
mov
- al imm b0
- cl imm b1
- dl imm b2
- bl imm b3
- ah imm b4
- ch imm b5
- dh imm b6
- bh imm b7
- (reg 8bit) (reg 8bit) 8a
- al (mem byte dir addr) a0
- (reg 8) (mem byte) 8a
- (mem byte) imm c6
- (mem byte dir) al a2
- (mem byte) (reg 8) 88
</pre>
---
##
---
