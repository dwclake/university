    [bits 32]
    global  _start

    section .text
_start:
    push  2                ; r
    push  6                ; n
    call  _MyPerm          ; calculate sum
    add   esp, 8           ; cleanup stack, mov result to edx

    ; sys_exit, returning sum
    mov   ebx, eax
    mov   eax, 1
    int   80h

_MyPerm:                   ; calculate n!/(n-r)!
    ; setup
    push  ebp
    mov   ebp, esp
    push  ebx
    push  ecx
    push  edi

numerator:                 ; calculate numerator
    mov   eax, 1           ; initialize eax to 1
    mov   ecx, [ebp + 8]   ; move n to ecx

    lea   edi, denominator ; load address to return to after factorial into edi
    jmp   factorial        ; calculate factorial of numerator

denominator:               ; calculate denominator
    mov   ebx, eax         ; move numerator to ebx for now
    mov   eax, 1           ; initialize eax to 1
    mov   ecx, [ebp + 8]   ; mov n to ecx again
    sub   ecx, [ebp + 12]  ; subtract r from n

    lea   edi, fraction    ; load address to return to after factorial into edi
    jmp   factorial        ; calculate factorial of denominator

fraction:                  ; calculate fraction
    xchg  eax, ebx
    div   ebx
    jmp   end

factorial:                 ; calculate factorial of ecx
    mul   ecx
    dec   ecx
    ; loop until ecx is zero
    jecxz factorial_end
    jmp   factorial

factorial_end:
    jmp   edi              ; jump to address in edi

end:
    ; cleanup
    pop   edi
    pop   ecx
    pop   ebx
    pop   ebp
    ret
