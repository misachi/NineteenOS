[bits 32]                   ; We are now in 32-bit Protected Mode
global pm_mode
pm_mode:                    ; Re-assign the segments appropriately. The segments assigned as previously
                            ; won't work as expected in PM mode. This means we have to manually re-assign
                            ; the segments correctly
                            
    mov ax, 0x10            ; The location 0x10 is the data descriptor
    mov ds, ax              ; We re-assign the ds - offset of 16bytes from the start(0x0)
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000        ; stack begins from 90000h
    mov esp, ebp

    call begin_pm

begin_pm:
    mov ebx, protected_mode_msg
    call print_string_pm 

    extern kernel_main

    mov eax, 0x2BADB002                         ; Magic Number to indicate to the operating system that it was loaded by a Multiboot-compliant boot loader  
    mov ebx, dword [boot_info]                  ; 32-bit physical address of the Multiboot information structure
    push dx
    push boot_info                              ; Place the multiboot structure on the stack(it's the argument to the main function)
    call kernel_main                            ; Call our kernel

; When our kernel returns, we ensure all interrupts are inactive before we
; halt the system
    cli
    hlt


%include "src/boot/Stage2/print_string_pm.asm"     ; 32bit mode
%include "src/boot/Stage2/paging.asm"

protected_mode_msg          db      0x0A, 0x0A, "Switched to Protected Mode", 0
