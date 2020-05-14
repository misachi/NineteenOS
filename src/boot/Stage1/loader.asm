;
; This is the first stage bootloader
; It contains the boot sector signature and loads
; the second stage from disk

KERNEL_SIZE equ 10                ; Approx Stage2 + Kernel size(No of sectors read)

[bits 16]
[org 0x7c00]                      ; sets the start address

    mov [BOOT_DRIVE], dl

    mov bp, 0x7c00                ; Our boot sector stack here at 9000h
    mov sp, bp

    call load_disk

    mov dx, KERNEL_SIZE           ; No of sectors read. This is an appoximation
    jmp 0x7e00                    ; Jump to second stage


load_disk:
    mov ax, 0x0
    mov es, ax
    mov bx, 0x7e00

    mov dh, 20
    mov dl, [BOOT_DRIVE]

    call read_dsk
    ret

%include "src/boot/Stage2/read_disk.asm"

BOOT_DRIVE         db      0

    times 510-($-$$) db 0

    dw 0xaa55
