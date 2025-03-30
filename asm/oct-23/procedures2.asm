          global  _start


          section .data
x:        dq      12
y:        dq      13

          section .text
_start:
          ; swap
          ; lea rax, x
          ; push rax
          ; lea rax, y
          ; push rax
          push    x
          push    y

          call    swap
          
          add     rsp, 16

          mov     rax, 5

          call    factorial

          mov     rbx, rax

          ; sys_exit
          mov     rax, 60
          mov     rdi, rbx
          syscall
swap:
          ; setup
          push    rbp
          mov     rbp, rsp
          ; rax assumed to be modified by procs in 32-bit
          ; so not needed in 32-bit
          push    rax
          push    rbx
          push    rcx
          push    rdx

          mov     rax, [rbp + 16]
          mov     rbx, [rbp + 24]
          mov     rcx, [rax]
          mov     rdx, [rbx]
          mov     [rax], rdx
          mov     [rbx], rcx

          ; cleanup
          pop     rdx
          pop     rcx
          pop     rbx
          pop     rax
          pop     rbp
          ret
factorial: 
          ; setup
          push    rbp
          mov     rbp, rsp
          push    rcx

          mov     rcx, [rbp + 16]

          cmp     rcx, 1
          jg      l1
          mov     rax, 1
          jmp     lend
l1:       
          dec     rcx
          push    rcx
          call    factorial
          inc     rcx
          imul    rcx
lend:
          ; cleanup
          pop     rcx
          pop     rbp
          ret
