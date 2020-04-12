; Print strings in 32 bit PM
; Heavily borrowed from https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

[bits 32]
VIDEO_MEMORY        equ         0xb8000
CHAR_ATTRIBUTE      equ         63                  ; the colour byte for each character

COLS                equ         80
LINES               equ         25

_CUR_X              db          0
_CUR_Y              db          0

print_pm:
    pusha
    mov edx, VIDEO_MEMORY

    mov al, COLS*2
    mov cl, byte [_CUR_Y]
    mul cl
    push eax

    mov al, byte [_CUR_X]
    mov cl, 2
    mul cl

    pop ecx
    add eax, ecx

    add edx, eax

    cmp bl, 0x0A
    je .new_line

    mov al, bl
    mov ah, CHAR_ATTRIBUTE
    mov word [edx], ax

    inc byte [_CUR_X]
    jmp .done

.new_line:
    mov byte [_CUR_X], 0
    inc byte [_CUR_Y]

.done:
    popa
    ret

print_string_pm:
    pusha
    mov edi, ebx

.string_pm_loop:
    mov ebx, [edi]
    cmp ebx, 0
    je .done
    call print_pm
    inc edi
    jmp .string_pm_loop

.done:
    popa
    ret
