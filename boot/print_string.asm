; Print string in 16-bit real mode using
; BIOS routines

print_real:
    lodsb                   ; Get next byte. Load al with value from si and increment si
    cmp al, 0x0             ; Check if we've reached end of string, 0

    je done                 ; Return if we are at the end of the string

    mov ah, 0x0e            ; call BIOS routine(0xe) of interrupt 0x10
    int 0x10           
      
    jmp print_real          ; Loop until string is empty

done:
    ret