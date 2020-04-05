;
; A simple boot sector program
;
[bits 16]
[org 0x7c00] ; sets the start address

    mov bp, 0x9000
    mov sp, bp

    mov si, boot_msg
    call print_real         ; Print characters to screen

    mov si, init_msg
    call print_real

    mov si, end_msg
    call print_real

    mov si, real_mode_msg
    call print_real

    call start_switch

    jmp $

%include "print_string.asm"
%include "print_string_pm.asm"
%include "protected_mode.asm"

begin_pm:
    mov ebx, protected_mode_msg
    call print_string_pm

    jmp $                           ; Loop forever

boot_msg           db      "==> Booting NineteenOS", 0
init_msg           db      "==> Initializing...", 0
end_msg            db      "==> Machine booted and ready", 0
real_mode_msg      db      "==> Booted in Real Mode", 0
protected_mode_msg db      "==> Successfully switched to Protected Mode", 0

    times 510-($-$$) db 0 

    dw 0xaa55
