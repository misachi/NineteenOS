;
; A simple boot sector program
;
[bits 16]
[org 0x7c00] ; sets the start address

    mov si, print_char
    call print_real         ; Print characters to screen

    jmp $

%include "print_string.asm"

print_char: db "Booting NineteenOS", 0
wait_msg:    db "Initializing...", 0
boot_msg:    db "Machine booted and ready", 0

    times 510-($-$$) db 0 

    dw 0xaa55
