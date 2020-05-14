#include <memory.h>

void *kmalloc(void* base, uint32_t size){
    uint32_t temp = (uint32_t)base + sizeof(int)*size*8;
    return (void *)temp;
}