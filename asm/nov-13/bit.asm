    global  _start

    section .data
str1:  db   "0123456789", 0
str2:  db   "0123456789", 0
str3:  db   "0143456789", 0
str4:  db   "45", 0

    section .text
_start:
    ; move address of str1 to rsi
    lea  rsi, str1
    ; rbx is holding the init
    lea  rdi, str3
    ; 
    push str1
    ; compare strings
    call compare

    add rsp, 8

    mov rdx, rbx
    
    ; mov result to rdx
    ;mov  rdx, rax

    ;lea  rsi, str1
    ;lea  rdi, str4

    ;call scan

    ;mov rdx, rbx

    ; sys_exit, returning sum
    mov  rax, 60
    mov  rdi, rdx
    syscall

compare:
    ; setup
    push rbp
    mov  rbp, rsp
    push rcx
    
    ; assume equal
    mov  rax, 1
    mov  rcx, [rbp + 16]
    cld

loop_compare:    
    ; check for null terminator in first operand
    cmp  byte [esi], 0 
    je   end_compare

    ; check for null terminator in second operand
    cmp  byte [edi], 0
    je   end_compare

    ; compare characters, if not eq jump, otherwise loop
    cmpsb
    jne  noteq
    jmp  loop_compare

noteq:
    mov  rbx, rsi
    sub  rbx, rcx
    mov  rax, 0

end_compare:
    ; cleanup
    pop  rcx
    pop  rbp
    ret

scan:
    ; setup
    push rbp
    mov  rbp, rsp
    push rcx

    cmp  byte [rsi], 0
    je end_scan
    
    cld
    mov  rbx, 0

loop_scan:
    mov ax, word [rdi]

    add  rbx, 1
    scasw
    je found

    dec  rsi

    cmp  byte [rsi], 0
    je  end_scan
    jmp  loop_scan
found:

end_scan:
    ; cleanup
    pop  rcx
    pop  rbp
    ret
