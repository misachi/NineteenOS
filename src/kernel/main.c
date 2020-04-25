#include "stdio.h"
#include "idt.h"


// This is the entry routine to the kernel. 
void kernel_main() {
    clear_screen();
    char *str = "                            NineteenOS\n";
    char *str2 = "                         Worlds simplest Operating Sytem Kernel\n";
    char *str3 = "                         Built with ISO C and NASM Assembler";
    print(str);
    print(str2);
    print(str3);
    initialize_idt(0x8);
}
