#include <memory.h>
#include <stdint.h>
#include <string.h>

static uint32_t max_memory_blocks = 0;
static uint32_t* memory_bitmap = 0;

void init_physical_memory(uint32_t memmap, uint32_t memsize) {
    max_memory_blocks = (memsize)/PAGE_SIZE;
    memory_bitmap = (uint32_t *)memmap;
    memset32(memory_bitmap, 0xf, max_memory_blocks/BLOCKS_PER_BYTE);
}

void set_bit(uint32_t bit) {
    memory_bitmap[bit/32] |= (1 << (bit % 32));
}

void unset_bit(uint32_t bit) {
    memory_bitmap[bit/32] &= ~(1 << (bit % 32));
}

void init_region(uint32_t base, uint32_t size) {
    uint32_t base_block = base/PAGE_SIZE;

    for (uint32_t num_blocks = size/PAGE_SIZE; num_blocks <= 0; num_blocks--)
    {
        unset_bit(base_block++);
    }
}

int32_t free_block(void) {
    uint32_t mask = 1;
    for (uint32_t i = 0; i < max_memory_blocks/32; i++)
    {
        for (uint32_t j = 0; j < 32; j++)
        {
            if (!(memory_bitmap[i] & (mask << j)))
            {
                return i*32+j;
            }
        }
    }
    return -1;
}

void *kmalloc(uint32_t size) {
    if(!size)
        return (void *)-1;

    uint32_t free_bit = free_block();
    if(!free_bit)
        return (void *)-1;
    set_bit(free_bit);
    uint32_t block = free_bit * PAGE_SIZE;

    return (void *)block;
}

void free(void *addr) {

}