section .data
msg db 'Hello, World!', 0Ah

section .text
global _start

_start:
    mov rax, msg
    call strlen

    mov rdx, rax
    mov rcx, msg
    mov rbx, 1
    mov rax, 4
    int 80h

    mov rbx, 0
    mov rax, 1
    int 80h

strlen:
    push rbx
    mov rbx, rax

nextchar:
    cmp byte [rax], 0
    jz finished
    inc rax
    jmp nextchar

finished:
    sub rax, rbx
    pop rbx
    ret
