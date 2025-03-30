# LV3A - Elements of Assembly Language - Statements
---
## Statements
- Comments start with ;
- Directives start with .
  - Used for program 'initialization' by assembler

```(asm)
; Program to ...
; Author: ... Date: ...

.586
.model flat
.stack 4096
.data
number DWORD -105
sum    DWORD ?
.code

COMMENT &
this is
a
comment
also
&

main PROC
        mov eax, number ; first number to EAX
ADDNOW: add eax, 158 ; ADDNOW -> label
        mov sum, eax ; mov -> mnemonics
        mov eax, 0
        ret
main ENDP
END
```
---
## Statements
- Instructions
  - Get translated into object code
- Directives
  - Tells the assembler to take specific actions
- Macros
  - Shorthand for a sequence of statements
---
## Instructions
- Each corresponds to a single instruction actually executed by the 80x86 CPU
- Examples
  - mov eax, number
    - copies a doubleword form memory to the accumulator EAX
  - add eax, 158
    - adds the doubleword representation of 158 to the number already in EAX, replacing that number
---
## Instructions Cont.
- Assembled into machine code by assembler
- Executed at runtime by the CPU
- We use intel IA-32 instruction set
- An instruction contains:
  - Labels (optional, can be used for 'looping/jumping')
  - Mnemonics (required)
  - Operands (depends on instruction, 'arguments')
  - Comments (optional)
- Little endian only applies to numbers stored in memory, not registers
---
## Labels
- Act as place markers
- marks the address (offset) of code and data
- follow identifier rules
- Data label:
  - must be unique
  - not followed by a colon
  - followed by size, DWORD BYTE WORD ...
  - size followed by initial value, ? for uninitialized
- Code label:
  - target of jump and loop instructions
  - followed by a colon
---
## Operands
- constant
- constant expression
- register
- memory (data label)
- Constants and constant expressions are often called immediate values
---
## Instruction format
- No operands
  - stc ; set carry flag
- One operands
  - inc eax ; increment content of register
  - inc myByte ; increment content of memory location
- Two operands
  - add ebx, eax ; register, register
  - sub myByte, 25 ; memory, constant
  - add eax, 36 * 25 ; register, constant-expression
---
## Directives
- Provide instructions to the assembler program
- Typically don't cause code to be generated
- Examples
  - .586 - tells assembler to use 32-bit architecture
  - DWORD - tells assembler to reserve space for a 32-bit integer value
- Commands that are recognized and acted upon by the assembler
- not case sensitive
- Different assemblers have different directives
- NASM not the same as MASM
---
## Macros
- Shorthand for a sequence of statements, think functions
- The assembler expands a macro to the statements it represents
```
MyMacro MACRO Param1, Param2
    ; put sum of two doubleword parameters in EAX
    mov eax, Param1
    add eax, Param2
ENDM

MyMacro ecx, 12
```
---
## Typical Statement Format
- (Label) Mnemonic (Operands) (;Comment)
---
## Identifiers
- letters, digits, special characters(avoid)
- may not begin with a digit
- may have up to 247 characters
- cannot use keywords(directives, mnemonics, register designations)
---
## Program Format
- Ident for readability, try to align mnemonics
- not case-sensitive
  - use lowercase for instructions
  - use uppercase for directives
---