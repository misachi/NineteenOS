[bits 16]
entry_count equ 0x8000

PhysicalMemorySize64:
    push ecx
	push edx
    xor ecx, ecx
    xor edx, edx
    mov ax, 0xE801
    int 0x15
    jc .error
    cmp	ah, 0x86		; unsupported function
	je	.error
	cmp	ah, 0x80        ; invalid command
    je .error
    jcxz .useax
    mov ax, cx
    mov bx, dx

.useax:
; AX = number of contiguous Kb, 1M to 16M
; BX = contiguous 64Kb pages above 16M
    pop edx
    pop ecx
    ret

.error:
    mov si, Error_MSG
    call print_real
    mov ax, -1
    mov bx, 0
    pop edx
    pop ecx
    ret

PhysicalMemoryMap:
    push bp
    mov bp, 0x0
    mov di, 0x1000
    mov eax, 0xE820
    xor ebx, ebx
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
    jecxz .check_term
    inc bp
    add di, 24

.check_term:
    test ebx, ebx
    jne .next_entry
    jmp .done

.done:
    mov [entry_count], bp               ; Store entry count
    pop bp
    ret

.error:
    mov si, Error_MSG
    call print_real
    mov [entry_count], word 0x0
    pop bp
    stc
    ret


Error_MSG db "Error Occured", 0
