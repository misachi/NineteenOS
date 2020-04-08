;
; A simple boot sector program
;

[bits 16]
[org 0x7c00]                      ; sets the start address

    mov [BOOT_DRIVE], dl
    mov bp, 0x9000                ; Our boot sector stack here at 9000h
    mov sp, bp

    mov si, real_mode_msg
    call print_real

    call load_kernel

    call start_switch

    jmp $

[bits 16]
load_kernel:
    mov si, kernel_load_msg
    call print_real

    mov ax, 0x0
    mov es, ax
    mov bx, 0x1000                  ; Buffer to read sectors to i.e es:bx - 0:0x1000

    mov dh, 16
    mov dl, [BOOT_DRIVE]

    call read_dsk
    ret

[bits 32]
begin_pm:
    mov ebx, protected_mode_msg
    call print_string_pm

    call 0x1000

    jmp $                            ; Loop forever

%include "print_string.asm"
%include "gdt.asm"          
%include "print_string_pm.asm"
%include "protected_mode.asm"
%include "read_disk.asm"

BOOT_DRIVE         db      0
real_mode_msg      db      "==> Booted in Real Mode", 0
protected_mode_msg db      "==> Successfully switched to Protected Mode", 0
kernel_load_msg    db      "==> Loading Kernel...", 0

    times 510-($-$$) db 0 

    dw 0xaa55
