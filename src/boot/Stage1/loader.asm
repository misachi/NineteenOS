;
; This is the first stage bootloader
; It contains the boot sector signature and loads
; the second stage from disk

KERNEL_SIZE equ 25                ; Approx Stage2 + Kernel size(No of sectors read)
STAGE2_ADDR equ 0x9000

[bits 16]
[org 0x7c00]                      ; sets the start address

    xor ax, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7c00

    mov [BOOT_DRIVE], dl

    call load_stage2
    call map_kernel_1mb
    call enablea20

    mov dx, KERNEL_SIZE               ; No of sectors read. This is an appoximation
    jmp STAGE2_ADDR                    ; Jump to second stage


load_stage2:
    mov ax, 0x0
    mov es, ax
    mov bx, STAGE2_ADDR

    mov dh, KERNEL_SIZE
    mov dl, [BOOT_DRIVE]
    mov cl, 0x02                    ; Boot sector is in the first sector so
                                    ; we start reading from the second sector

    call read_dsk
    ret

%include "src/boot/Stage2/read_disk.asm"
%include "src/boot/Stage2/a20.asm"


BOOT_DRIVE                  db      0

    times 510-($-$$) db 0

    dw 0xaa55
