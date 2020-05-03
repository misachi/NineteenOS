[bits 16]
entry_count equ 0x8000

PhysicalMemorySize64:
    pusha
    xor cx, cx
    xor dx, dx
    mov ax, 0xE801
    call 0x15
    jc .error
    cmp	ah, 0x86		; unsupported function
	je	.error
	cmp	ah, 0x80        ; invalid command
    je .error
    jcxz .useax
    mov ax, cx
    mov bx, dx

.error:
    mov ax, -1
    mov bx, 0
    popa
    ret

.useax:
; AX = number of contiguous Kb, 1M to 16M
; BX = contiguous 64Kb pages above 16M
    popa
    ret


PhysicalMemoryMap:
    mov di, 0x8004
    xor eax, eax
    mov eax, 0xE820
    mov ebx, 0
    mov ecx, 24
    mov edx, 0x534D4150                 ; 'SMAP'
    mov [es:di + 20], dword 1
    int 0x15
    jc  .error
    cmp eax, 0x534D4150
    jne .error
    test ebx, ebx
    je .error
    jmp .start

.next_entry:
    mov ecx, 24
    mov eax, 0xE820
    mov edx, 0x0534D4150                ; in case register is trashed
    mov [es:di + 20], dword 1
    int 0x15

.start:
    jcxz .check_term

.notext:
    mov ecx, [es:di + 8]
    or ecx, [es:di + 12]
    jecxz   .check_term
    inc bp
    add di, 24

.check_term:
    test ebx, ebx
    jne .next_entry
    jmp .done

.error:
    stc
    ret

.done:
    mov [entry_count], bp           ; Store entry count
    ret
