[bits 32]
global load_directory
global enable_paging

load_directory:
    push ebp
    mov ebp, esp
    mov eax, dword [esp+8]
    mov cr3, eax
    mov esp, ebp
    pop ebp
    ret


enable_paging:
    push ebp
    mov ebp, esp
    mov eax, cr0
    or eax, 0x80000000
    mov eax, cr0
    pop ebp
    ret
