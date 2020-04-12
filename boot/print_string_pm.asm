; Print strings in 32 bit PM
; Heavily borrowed from https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

[bits 32]
VIDEO_MEMORY equ 0xb8000
CHAR_ATTRIBUTE equ 63         ; the colour byte for each character

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

    .print_string_pm_loop:
        mov al, [ebx]
        mov ah, CHAR_ATTRIBUTE

        cmp al, 0
        je .print_string_pm_done

        mov [edx], ax               ; Store character and output in video memory
        add ebx, 1                  ; Next char
        add edx, 2                  ; Next video memory position
        jmp .print_string_pm_loop

    .print_string_pm_done:
        popa
        ret