#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define PAGE_SIZE 4096
#define BLOCKS_PER_BYTE 8  // 1 Byte addresses 8 blocks

void init_physical_memory(uint32_t memmap, uint32_t size);
void init_region(uint32_t base, uint32_t size);
void set_bit(uint32_t bit);
void unset_bit(uint32_t bit);
int32_t free_block(void);
void *kmalloc(uint32_t);
void free(void *addr);
void protect_kernel(uint32_t base, uint32_t size);
#endif
