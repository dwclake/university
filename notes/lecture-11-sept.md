# Mon 11 Sept 2023
---
## Direct vs Indirect Memory Addressing
Three Addressing Modes (ways to 'retrieve' data):
    - Immediate
    - Register
    - Memory
```
.data
number DWORD ?
number2 DWORD 0
...
    mov eax, 20
    mov eax, number ; copy from number to number2, cannot directly move from number to number2
    mov number2, eax

    mov number, 20
    or
    lea EBX, number ; loads address of number into EBX
    mov [EBX], 20 ; follows address stored in EBX, and stores 20 at that address

    lea EBX, number ; If number was an array, you must use indirect addressing to access elements
    mov [EBX] + number2, number2
    inc number2
```
EAX - register mode,
20 - immediate mode,
number - memory mode,
[EBX] - Indirect memory addressing, treats EBX as a pointer and dereferences it


Direct: Use the value at the memory address,
Indirect: Use the value at the memory address as an address,
Registers are the fastest memory available.

Little-Endian applies to any multibyte value being stored/read in/from memory

---
