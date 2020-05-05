; Print strings in 32 bit PM

[bits 32]
VIDEO_MEMORY        equ         0xb8000
CHAR_ATTRIBUTE      equ         0x0f                  ; the colour byte for each character(Black on White)

COLS                equ         80
LINES               equ         25

_CUR_X              db          0                   ; The x/y position
_CUR_Y              db          0

print_pm:
; Print a single character on screen
    pusha
    mov edx, VIDEO_MEMORY                           ; Set Video memory start address

    mov al, COLS*2                                  ; Every character is represented by 2 bytes in memory. As a result we store
                                                    ; the 2-byte column value in al 
    mov cl, byte [_CUR_Y]
    mul cl
    push eax                                        ; Store EAX value(Y * COLS * 2) on the stack

    mov al, byte [_CUR_X]
    mov cl, 2
    mul cl

    pop ecx                                          ; Get the value of EAX on the stack
    add eax, ecx

    add edx, eax

    cmp bl, 0x0A                                     ; Handle new line character i.e the ASCII value of new line is 0x0A
    je .new_line

    mov al, bl
    mov ah, CHAR_ATTRIBUTE
    mov word [edx], ax

    inc byte [_CUR_X]                                ; Get next position to be written
    jmp .done

.new_line:
    mov byte [_CUR_X], 0
    inc byte [_CUR_Y]

.done:
    popa
    ret

print_string_pm:
    pusha
    mov edi, ebx

.string_pm_loop:
    mov bl, [edi]              ; Set EBX to the next character
    cmp bl, 0                  ; Check if we are at the end the string
    je .done                    ; If we are, the we are done printing and should return to caller
    call print_pm               ; Print the next character
    inc edi                     ; Get next character
    jmp .string_pm_loop         ; Loop through the string

.done:
; Before we return control, we must change the cursor position on screen.
; We do this by setting the bx register appropriately - BH is set to Y position 
; while BL is set to X position.
    mov bh, byte [_CUR_Y]       
    mov bl, byte [_CUR_X]
    call mov_cur

    popa
    ret

mov_cur:
; Enable cursor to to move on screen when characters are printed.
; This function requires 2 paramenters i.e register bx must be set
; such that bh is the Y position and bl is the X position on screen
    pusha
    xor eax, eax            ; Clear EAX register

; Get current position relative to screen and not memory
; thus we don't need the byte momory alignement here. We use directl
; the formula X + Y * 80 to get the cursor position
    mov cl, COLS
    mov al, bh
    mul cl
    add al, bl
    mov ebx, eax

; Here we go ahead to set the necessary ports for our CRT Microcontroller.
; The cursor position is at offsets 0x0E(high byte) and 0x0F(low byte). We first
; indicate we are setting the low byte(0x0f) by setting the index register(port 0x03D4)
; then send the X position(BL) to the Data register port(0x03D5). We do the same
; for the high byte(Y position which is BH)
    mov	al, 0x0f
	mov	dx, 0x03D4
	out	dx, al

    mov al, bl
    mov dx, 0x03D5
    out dx, al

    mov al, 0x0e
    mov dx, 0x03D4
    out dx, al

    mov al, bh
    mov dx, 0x03D5
    out dx, al

    popa
    ret
