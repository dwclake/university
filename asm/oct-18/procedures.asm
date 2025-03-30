          global  _start


          section .data
x:        dq      12
y:        dw      13
message:  db      "hello, world", 10

          section .text
_start:
          ;sys_write
          mov     rax, 1
          mov     rdi, 1
          lea     rsi, message
          mov     rdx, 13
          syscall

          ; rev
          push    qword [x]

          call    rev

          pop     qword [x]

          ; sum
          push    word [x]
          push    word [y]

          call    sum

          pop     word [y]
          pop     word [x]

          ; sys_exit
          mov     rax, 60
          mov     rdi, r9
          syscall
rev:
          push    rbp
          mov     rbp, rsp
          push    rax

          mov     rax, [rbp + 16]
          neg     rax
          mov     r8, rax
          
          pop     rax
          pop     rbp
          ret
sum:   
          push    rbp
          mov     rbp, rsp
          push    rbx
          push    rax

          mov     rbx, [rbp + 16] 
          mov     rax, [rbp + 18]
          add     rax, rbx
          mov     r9, rax

          pop     rax
          pop     rbx
          pop     rbp
          ret
