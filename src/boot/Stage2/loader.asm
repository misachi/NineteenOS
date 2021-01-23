;
; Second stage bootloader
; Boots into our C Kernel

[bits 16]
; This should be included before we create a multiboot structure instance
; else, for some reason, we get an error <error: non-constant argument supplied to TIMES>
%include "src/boot/Stage2/multiboot.asm"

; The multiboot info structure instance
boot_info:
istruc multiboot_info
    at multiboot_info.flags,                    dd  0
    at multiboot_info.mem_lower,                dd  0
    at multiboot_info.mem_upper,                dd  0
    at multiboot_info.boot_device,              dd  0
    at multiboot_info.cmdline,                  dd  0
    at multiboot_info.mods_count,               dd  0
    at multiboot_info.mods_addr,                dd  0
    at multiboot_info.syms0,                    dd  0
    at multiboot_info.syms1,                    dd  0
    at multiboot_info.syms2,                    dd  0
    at multiboot_info.mmap_length,              dd  0
    at multiboot_info.mmap_addr,                dd  0
    at multiboot_info.drives_length,            dd  0
    at multiboot_info.drives_addr,              dd  0
    at multiboot_info.config_table,             dd  0
    at multiboot_info.boot_loader_name,         dd  0
    at multiboot_info.apm_table,                dd  0
    at multiboot_info.vbe_control_info,         dd  0
    at multiboot_info.vbe_mode_info,            dd  0
    at multiboot_info.vbe_mode,                 dw  0
    at multiboot_info.vbe_interface_seg,        dw  0
    at multiboot_info.vbe_interface_off,        dw  0
    at multiboot_info.vbe_interface_len,        dw  0
    at multiboot_info.framebuffer_addr,         dq  0
    at multiboot_info.framebuffer_pitch,        dd  0
    at multiboot_info.framebuffer_width,        dd  0
    at multiboot_info.framebuffer_height,       dd  0
    at multiboot_info.framebuffer_bpp,          db  0
    at multiboot_info.framebuffer_type,         db  0
    at multiboot_info.color_info,               dd  0
iend

stage2:
    mov [BOOT_DRIVE], dl

    cli	                            ; clear interrupts
	xor	ax, ax                      ; null segments
	mov	ds, ax
	mov	es, ax
    mov bp, 0x9000                  ; Our boot sector stack here at 9000h
    mov sp, bp
    sti

    ;Clear the screen
    mov ax, 03h
    int 10h

    mov si, real_mode_msg
    call print_real

    mov byte [boot_info+multiboot_info.boot_device], dl         ; BootDrive in use
    xor	eax, eax
	xor	ebx, ebx
    call PhysicalMemorySize64                                   ; Get physical memory size
    mov word [boot_info+multiboot_info.mem_lower], ax           ; Number of contiguous KB between 1 and 16 MB, maximum 0x3C00 = 15 MB.
    mov word [boot_info+multiboot_info.mem_upper], bx           ; Number of contiguous 64 KB blocks between 16 MB and 4 GB

    call PhysicalMemoryMap
    mov [boot_info+multiboot_info.mmap_addr], word 0x1000

    call switch_pm                                           ; Switch to stage3, which is the Protected Mode

    jmp $


; We are still in 16-bit Real Mode
switch_pm:                  ; Begin the swith to 32-bit Protected mode(PM)
    cli                     ; Stop all interrupts
    lgdt [gdtr_reg]         ; Load our GDT using our label from before into the gdt register

    mov  eax, cr0           ; We turn on the first bit of control register(cr0) in order to
                            ; switch to PM
    or   eax, 0x1
    mov  cr0, eax

    jmp  0x08:pm_mode       ; Make a far jump to 32-bit PM segment. The purpose for this is to
                            ; enable the cpu to flush all interrupts and register before
                            ; moving to PM mode. 0x08 is the offset for the code descriptor. This sets
                            ; the cs registers as well

%include "src/boot/Stage2/gdt.asm"
%include "src/boot/Stage2/print_string.asm"        ; 16bit print
%include "src/boot/Stage2/memory.asm"
%include "src/boot/Stage2/protected_mode.asm"

BOOT_DRIVE                  db      0
real_mode_msg               db      "Booting into Real Mode", 0
