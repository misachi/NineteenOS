#include <stdio.h>
#include <idt.h>
#include <multiboot.h>

// This is the entry routine to the kernel. 
void kernel_main(multiboot_info *memory_size){
    uint32_t *count = (uint32_t *)0x8000;
    clear_screen();
    printf("\n\n\n                            NineteenOS\n");
    printf("                         Worlds simplest Operating Sytem Kernel\n");
    printf("                       Built with ISO C and NASM Assembler");
    initialize_idt(0x8);
}
