#ifndef _MEMORY_H
#define _MEMORY_H

#include "../../Include/stdint.h"

#define DEBUG_ENABLED 1
#define PAGE_SIZE 4096
#define BLOCKS_PER_BYTE 8  // 1 Byte addresses 8 blocks

typedef uint32_t physical_addr_t;

void init_physical_memory(physical_addr_t memmap, uint32_t size);
void init_region(physical_addr_t base, uint32_t size);
int32_t unused_block(void);
int32_t unused_blocks(uint32_t size);
void *kmalloc(uint32_t);
void free(void *addr);
void protect_kernel(physical_addr_t base, uint32_t size);
void debug_mem(void);
#endif
