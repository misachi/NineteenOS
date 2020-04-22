#include "stdio.h"
#include "idt.h"


// This is the entry routine to the kernel. 
void kernel_main() {
    char *str = "\nNineteenOS";
    print(str);
    initialize_idt(0x8);
}
