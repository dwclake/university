    global  _start

    section .text
_start:
    ; sum first n in [1,3,5,7,9...]
    mov  rax, 0
    ; rbx is holding the init
    mov  rbx, 1
    ; rcx is holding n
    mov rcx, 4
    
    jmp loop
add:
    add  rax, rbx
    jmp  loop + 2
loop:    
    ; add rbx to sum
    jmp  add
    ; add 2 to rbx, dec rcx
    add  rbx, 2 
    dec  rcx

    ; if rcx > 0, loop, else end
    cmp  rcx, 0
    jg   loop
end:
    ; mov total to rdx
    mov  rdx, rax

    ; sys_exit, returning sum
    mov  rax, 60
    mov  rdi, rdx
    syscall
