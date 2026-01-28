section .data
msg db 'Hello, World!', 0Ah
a db 'Anushk', 0Ah

section .text
global _start

_start:
    mov edx, 13 ;; Allocate 13 bytes to write Hello, World!
    mov ecx, msg
    mov ebx, 1
    mov eax, 4
    int 80h

    mov edx, 6
    mov ecx, a
    mov ebx, 1
    mov eax, 4
    int 80h

    mov ebx, 0
    mov eax, 1
    int 80h
