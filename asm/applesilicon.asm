.global _start
.align 2

_start:
    mov x0, 1
    adr x1, hello_world
    mov x2, 14
    mov x16, 4
    svc 0x80

    mov x0, 0
    mov x16, 1
    svc 0x80

hello_world: .asciz "Hello, World!\n"
