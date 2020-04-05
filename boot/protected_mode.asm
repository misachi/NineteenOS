[bits 16]                   ; We are still in 16-bit Real Mode
%include "gdt.asm"          ; Import our table

start_switch:               ; Begin the swith to 32-bit Protected mode(PM)
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

[bits 32]

pm_mode:                    ; Re-assign the segments appropriately. The segments assigned as previously
                            ; won't work as expected in PM mode. This means we have to manually re-assign
                            ; the segments correctly
                            
    mov ax, 0x10            ; The location 0x10 is the data descriptor
    mov ds, ax              ; We re-assign the ds - offset of 16bytes from the start(0x0)
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000h       ; stack begins from 90000h
    mov esp, ebp
