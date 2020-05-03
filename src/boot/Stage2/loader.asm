;
; Second stage bootloader
; Boots into our C Kernel

[bits 16]
start:
    mov [BOOT_DRIVE], dl

    mov bp, 0x9000                ; Our boot sector stack here at 9000h
    mov sp, bp

    mov si, real_mode_msg
    call print_real

    call start_switch

    jmp $

[bits 32]
begin_pm:
    mov ebx, protected_mode_msg
    call print_string_pm

    extern kernel_main
    call kernel_main
    cli
    hlt                                     ; Loop forever

%include "src/boot/Stage2/gdt.asm"
%include "src/boot/Stage2/print_string.asm"        ; 16bit print
%include "src/boot/Stage2/print_string_pm.asm"     ; 32bit mode
%include "src/boot/Stage2/protected_mode.asm"
%include "src/boot/Stage2/memory.asm"

BOOT_DRIVE         db      0
protected_mode_msg db      "Switched to Protected Mode", 0
real_mode_msg      db      "==> Real Mode", 0
