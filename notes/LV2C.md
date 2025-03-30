# LV2C - Parts of a Computer System - Registers
---
## 80x86 Registers
- Internal to CPU, rapidly accessed
- Used in arithmetic and other operations
- Register file/set - The collection of registers
- 64-bit CPUs have more registers each of which are typically larger

---
## General Registers, 32-bit CPU
- Available on 386 and higher processors
  - 386 = 32-bit x86
- Most allow access to 16 or 8 bit sections, for backwards compatibility of code
- General Purpose Registers: [32-bit]
  - EAX, EBX, ECX, EDX
  - ESI EDI EBP ESP
- Segment Registers: [16-bit, available for backwards compatibility]
  - CS, DS, ES, FS, GS, SS
- Instruction Pointer: EIP [32-bit]
  - Points to next instruction to be fetched
- Flags Register: EFLAGS [32-bit]
  - Gives flags/signals to signify errors, etc. Each bit is it's own signal
- E: Extended, 32-bit register

---
## General Registers Continued
<pre>
31            16 15       8 7       0    16-bit  32-bit
                 [   AH   ] [   AL  ]      AX      EAX
                 [   BH   ] [   BL  ]      BX      EBX
                 [   CH   ] [   CL  ]      CX      ECX
                 [   DH   ] [   DL  ]      DX      EDX
                 [        BP        ]              EBP
                 [        SI        ]              ESI
                 [        DI        ]              EDI
                 [        SP        ]              ESP
</pre>
---
## E*X General Registers, 32-bit CPU
EAX, AX, AH, AL:
  - Accumulator register
  - Arithmetic, I/O port access, interrupt calls, etc.
EBX, BX, BH, BL:
  - Base register
  - Used as the base pointer for memory access, gets some interrupt return values
ECX, CX, CH, CL:
  - Counter register
  - Used as a loop counter and for shifts, gets some interrupt values
EDX, DX, DH, DL:
  - Data register
  - Used for I/O port access, arithmetic, some interrupt calls
---
## E*I General Registers, 32-bit CPU
Index registers:
  - ESI, SI:
    - Source index
    - Source address in string moves
    - Array index
    - General purposes
  - EDI, DI:
    - Destination index
    - Destination address in string moves
    - Array index
    - General purposes
---
## E*P General Registers, 32-bit CPU
Pointer registers:
  - ESP:
    - Stack pointer
    - Hold address to top of stack
  - EBP:
    - Base pointer
    - Used in procedure calls to hold address of reference point in the stack
---
## Segment Registers
6 segment registers
  - CS, DS, ES, FS, SS, GS
  - Each 16-bits long holding a segment selector
  - With flat memory model, managed by operating system
  - Hold the segment address of various items
---
## Other Registers, 32-bit CPU
EIP:
  - Instruction pointer
  - Holds address of next instruction to be fetched
EFLAGS:
  - Collections of flags, or status bits
  - Records information about many operations
    - Carry flag is Bit 0
    - Zero flag is Bit 6
    - Sign flag is Bit 7
    - Overflow flag is Bit 11
---
## Registers in 64-bit CPU
RAX, RBX, RCX, RDX, RSI, RDI, RSP, RBP, RIP, RFLAGS:
  - Extends the 32-bit registers
  - Lower 32-bit can be accessed with E*X
R8-R15:
  - New 64-bit general use registers
  - Lower 32-bit can be accessed with R*D (double word)
  - Lower 16-bit can be accessed with R*W (word)
  - Lower 8-bit can be accessed with R*B (byte)
---
