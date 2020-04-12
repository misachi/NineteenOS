; Read disk sectors during boot process

[bits 16]

; Reset floppy drive to ensure we read bytes
; from the first sector. Retry twice then exit(return to caller).
; This is done in speculation that the disk might not be ready at the
; first trial. An attempt to read disk immediately fails(at least for me)
reset:
    pusha
    mov bx, 2       ; Retry at least twice to reset disk

reset_loop:
    dec bx
    cmp bx, 0
    je reset_done
    mov ah, 0
    mov dl, 0       ; Our drive is floppy disk(drive number 0)
    int 0x13        ; Call BIOS interrupt to access disk
    jmp  reset_loop      ; if carry flag is set, an error occurred,
                    ; Repeat process
reset_done:
    popa
    ret

read_dsk:
    push dx
    mov ah, 0x02    ; Routine to access disk
    mov al, dh      ; We read dh sectors
    mov cl, 0x02    ; Boot sector is in the first sector so
                    ; we start reading from the second sector

    mov ch, 0x00    ; Cylinder(track) 0
    mov dh, 0x00    ; We will read from top head(0)

    call reset

    int 0x13
    jc  disk_error  ; If CF is set, an error occured, call 
                    ; error handler
    pop dx
    cmp al, dh      ; BIOS also sets 'al' to the # of sectors read. Compare it.
    jne sector_mismatch
    ret

disk_error:
; If an error occurs, print error message and hang
    mov si, disk_error_msg
    call print_real
    jmp hang

sector_mismatch:
    mov si, sector_error_msg
    call print_real
    jmp hang

hang:
    jmp $

kernel_load_msg     db      "==> Loading Kernel...", 0
disk_error_msg      db      "Error while reading disk", 0
sector_error_msg    db      "Sector read and requested do not match", 0