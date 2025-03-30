    global  _start

    section .text
_start:
    ; sum first 10 in [1,3,5,7,9...]
    ; init
    push 1
    ; inc
    push 2
    ; count
    push 10
    ; calculate sum
    call sum
    ; cleanup stack, mov result to rdx
    add  rsp, 24
    mov  rdx, rax

    ; sys_exit, returning sum
    mov  rax, 60
    mov  rdi, rdx
    syscall
sum:
    ; setup
    push rbp
    mov  rbp, rsp
    push rbx
    push rcx
    push rdx

    mov  rax, 0
    ; rbx is holding the init
    mov  rbx, [rbp + 32]
    ; rdx is holding the inc
    mov  rdx, [rbp + 24]
    ; rcx is holding the count
    mov  rcx, [rbp + 16]
    ; if count is zero, jmp to end 
    jrcxz end
loop:    
    ; add rbx to sum
    jmp  add
    ; add rdx to rbx, dec rcx
    add  rbx, rdx 
    dec  rcx

    ; if rcx > 0, loop, else end
    cmp  rcx, 0
    jg   loop
    jmp  end
add:
    add  rax, rbx
    jmp  loop + 2
end:
    ; cleanup
    pop  rdx
    pop  rcx
    pop  rbx
    pop  rbp
    ret
