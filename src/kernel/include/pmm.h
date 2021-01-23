#ifndef _MEMORY_H
#define _MEMORY_H

#include "../../Include/stdint.h"

#define DEBUG_ENABLED 1
#define PAGE_SIZE 4096
#define BLOCKS_PER_BYTE 8  // 1 Byte addresses 8 blocks

void init_physical_memory(uint32_t memmap, uint32_t size);
void init_region(uint32_t base, uint32_t size);
int32_t unused_block(void);
void *kmalloc(uint32_t);
void free(void *addr);
void protect_kernel(uint32_t base, uint32_t size);
void debug_mem(void);
#endif
