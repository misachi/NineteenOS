null_seg:               ; null segment descriptor of GDT
                        ; We add another null 4bytes since each describtor is 8 
                        ; bytes in size.
    dd 0x0
    dd 0x0

code_seg:               ; code segment descriptor of GDT
                        ; Should begin at offset 0x8 i.e after 8 bytes form beginning
    dw 0xffff           ; Limit ( bits 0 -15)
    dw 0x0              ; Base ( bits 0 -15)
    db 0x0              ; Base ( bits 16 -23)
    db 10011010b        ; 1st flags , type flags
    db 11001111b        ; 2nd flags , Limit ( bits 16 -19)
    db 0x0              ; Base ( bits 24 -31)

data_seg:               ; Data segment decriptor of GDT. 
                        ; Begins after 16bytes of memory
    dw 0xffff           ; Limit ( bits 0 -15)
    dw 0x0              ; Base ( bits 0 -15)
    db 0x0              ; Base ( bits 16 -23)
    db 10010010b        ; 1st flags , type flags
    db 11001111b        ; 2nd flags , Limit ( bits 16 -19)
    db 0x0              ; Base ( bits 24 -31)

end_gdt:

gdtr_reg:               
    ; GDT register stores pointer to the GDT table
    ; We use it to store the size(limit) of the GDT and 
    ; base(where the GDT starts). We'll later on use it to load
    ; our GDT

    dw end_gdt - null_seg - 1   ; Size of GDT
    dd null_seg                 ; Start of GDT(Base)
    
