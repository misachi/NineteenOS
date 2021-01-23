; [bits 32]
; test_a20:
;     pushad
;     mov edi, 0x112345
;     mov esi, 0x012345 
;     mov [esi], esi
;     mov [edi], edi
;     cmpsd
;     popad
;     jne .A20_on
;     ret

; .A20_on:
;     mov ebx, a20_on_msg
;     call print_string_pm
;     ret

[bits 32]
enablea20:
        cli
 
        call  .a20wait
        mov   al, 0xAD
        out   0x64, al
 
        call  .a20wait
        mov   al, 0xD0
        out   0x64, al
 
        call  .a20wait2
        in    al, 0x60
        push  eax
 
        call  .a20wait
        mov   al, 0xD1
        out   0x64, al
 
        call  .a20wait
        pop   eax
        or    al, 2
        out   0x60, al
 
        call  .a20wait
        mov   al, 0xAE
        out   0x64, al
 
        call  .a20wait
        sti
        ret
 
.a20wait:
        in    al, 0x64
        test  al, 2
        jnz   .a20wait
        ret
 
 
.a20wait2:
        in    al, 0x64
        test  al, 1
        jz    .a20wait2
        ret

a20_on_msg db 0x0A, "A20 is on", 0
