#include "../Include/string.h"
#include "../Include/stdio.h"
#include "../Include/stdint.h"
#include "./include/pmm.h"

static inline uint8_t check_bit_set(uint32_t bit);
static inline void set_bit(uint32_t bit);
static inline void unset_bit(uint32_t bit);

static physical_addr_t* memory_bitmap;
static uint32_t max_memory_blocks;
static uint32_t total_usable_blocks;
static uint32_t used_memory_blocks;

void init_physical_memory(physical_addr_t memmap, uint32_t memsize) {
    total_usable_blocks = 0;
    used_memory_blocks = 0;

    max_memory_blocks = memsize/PAGE_SIZE;
    memory_bitmap = (physical_addr_t *)memmap;
    memset(memory_bitmap, 0x0, max_memory_blocks/BLOCKS_PER_BYTE);
}

inline uint8_t check_bit_set(uint32_t bit) {
    return memory_bitmap[bit/32] & (1 << (bit % 32));
}

inline void set_bit(uint32_t bit) {
    if (check_bit_set(bit)) {
        return;
    }
    memory_bitmap[bit/32] |= (1 << (bit % 32));
}

inline void unset_bit(uint32_t bit) {
    if (!check_bit_set(bit)) {
        return;
    }
    memory_bitmap[bit/32] &= ~(1 << (bit % 32));
}

void init_region(physical_addr_t base, uint32_t size) {
    uint32_t num_blocks = size/PAGE_SIZE;
    physical_addr_t base_block = base/PAGE_SIZE;

    for (; num_blocks > 0; num_blocks--)
    {
        unset_bit(base_block++);
        ++total_usable_blocks;
    }
}

void protect_kernel(physical_addr_t base, uint32_t size) {
    uint32_t num_blocks = size/PAGE_SIZE;
    physical_addr_t base_block = base/PAGE_SIZE;

    for (; num_blocks > 0; num_blocks--)
    {
        set_bit(base_block++);
        ++used_memory_blocks;
    }
}

int32_t unused_block(void) {
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

int32_t unused_blocks(uint32_t size) {
    for (uint32_t i = 0; i < max_memory_blocks/32; i++)
    {
        for (uint32_t j = 0; j < 32; j++)
        {
            uint32_t ret = i*32+j;
            if (!(memory_bitmap[i] & (1 << j)))
            {
                uint32_t n = 1;
                while (n <= size && (!(memory_bitmap[i] & (1 << j))))
                {
                    if (n == size)
                        return ret;
                    n++;
                    j++;
                }
            }
        }
    }
    return -1;
}

void *kmalloc(uint32_t size) {
    int32_t free_bit;

    if (size < 2) {
        free_bit = unused_block();
        if(free_bit == -1){
            return 0;
        }
        set_bit(free_bit);
        used_memory_blocks++;
    } else {
        free_bit = unused_blocks(size);
        if(free_bit == -1){
            return 0;
        }
        for (uint32_t i = 0; i < size; i++)
        {
            set_bit(free_bit+i);
        }
        used_memory_blocks+=size;
    }

    int32_t block = free_bit * PAGE_SIZE;
    return (void *)block;
}

void free(void *addr) {
    uint32_t block  = (physical_addr_t)addr/PAGE_SIZE;
    unset_bit(block);
    used_memory_blocks--;
}

static uint32_t debug_get_size(uint32_t size) {
    return (size * PAGE_SIZE)/1024;
}

void debug_mem(void) {
#if defined(DEBUG_ENABLED)
    printf("\n      Detail: %d kib total system memory", debug_get_size(total_usable_blocks));
    printf("\n      Detail: %d kib max usable memory", debug_get_size(max_memory_blocks));
    printf("\n      Detail: %d blocks of memory in use", used_memory_blocks);
    printf("\n      Detail: %d kib unused memory", debug_get_size(total_usable_blocks - used_memory_blocks));
    if (used_memory_blocks) {
        printf("\n      Warning: %d blocks of memory not free'd", used_memory_blocks);
    }
#endif
}
