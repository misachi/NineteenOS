;
; A simple boot sector program
;
    mov ah, 0x0e
    ; booting_os  db "Booting NineteenOS", 0
    ; wait_msg    db "Initializing...", 0
    ; boot_msg    db "Machine booted and ready", 0

    mov bp, 0x7c00
    mov sp, bp

    mov al, [print_char]
    int 0x10                ; Print character to screen

    jmp $

print_char:
    db "K"

    times 510-($-$$) db 0 

    dw 0xaa55
