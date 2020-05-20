#include <stdio.h>
#include <stdint.h>
#include <idt.h>
#include <multiboot.h>
#include <memory.h>

typedef struct address_range_desc {
    uint32_t base_low;
    uint32_t base_high;
    uint32_t length_low;
    uint32_t length_high;
    uint32_t type;
	uint32_t acpi_3_0;
} __attribute__((packed)) address_range_desc_t;

// This is the entry routine to the kernel
void kernel_main(multiboot_info *memory_size, uint16_t ksize){
    uint16_t *count = (uint16_t *)0x8000;
    uint16_t kernel_size = ksize*512;
    uint32_t phy_memory_size = 1024 + (memory_size->mem_lower * 1024) + (memory_size->mem_upper * 64 * 1024);
    address_range_desc_t *region = (address_range_desc_t *)memory_size->mmap_addr;
    clear_screen();
    printf("\n\n\n                            NineteenOS\n");
    printf("                         Worlds simplest Operating Sytem Kernel\n");
    printf("                       Built with ISO C and NASM Assembler");
    initialize_idt(0x8);
    printf("\n\n                Physical Memory Size(Bytes): %u", phy_memory_size);
    printf("\n\n                Low memory(KB): 0x%x  Extended memory(KB) 0x%x", memory_size->mem_lower, memory_size->mem_upper * 64);
    printf("\n\n                Kernel Size(bytes): %d", kernel_size);
    printf("\n\n                               Memory Regions");
    printf("\n                            ---------------------");
    init_physical_memory((uint32_t)0x100000+kernel_size, phy_memory_size);
    for (uint8_t i = 0; i < *count; i++)
    {
        printf("\n          Region(%i) | Memory Address(0x%x%x)| Length(0x%x%x) | Type(%i)", i+1, region[i].base_high, region[i].base_low, region[i].length_high, region[i].length_low, region[i].type);
        if (region[i].type == 1) {
            init_region(region[i].base_low, region[i].length_low);
        }
    }

    uint32_t *foo = kmalloc(sizeof(uint32_t));
    uint32_t *bar = kmalloc(sizeof(uint32_t));
    printf("\n 0x%x", foo);
    printf("\n 0x%x", bar);
}
