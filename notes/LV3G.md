# LV3G - Elements of Assembly Language - Example 64-bit
---
##
<pre>
- not required .586, .model flat, .stack
- data segment uses QWORD
- Code segment uses RAX
- Exits by storing 0 in RAX followed by ret
</pre>
```asm
; console64 example
.data
number  qword -105
sum     qword ?

.code
main  PROC
      mov rax, number
      add rax, 158
      mov sum, rax
      mov rax, 0
      ret
main  ENDP
END
```
- "Direct memory addressing" is RIP (instruction pointer) relative, the
32-bit offset is added to the instruction pointer to get the address
- Extra code is required for windows64
- For procedure call, the caller reserves stack space for arguments
```asm
sub rsp, 120 ; reserve stack space for 15 args
add rsp, 120 ; restore stack
```
---
