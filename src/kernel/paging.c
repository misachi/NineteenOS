#include "./include/pmm.h"
#include "./include/paging.h"

extern void load_directory(page_directory_t *directory);
extern void enable_paging();

static page_directory_t page_directory[1024] __attribute__((aligned(4096)));

void create_page_directory() {
    page_directory[0] = (page_directory_t)kmalloc(sizeof(uint32_t));

    for(int i = 0; i < PAGE_DIRECTORY_SIZE; i++)
        page_directory[i] = PDE_BIT_READ_WRITE;
}

page_entry_t *create_page_table() {
    page_entry_t *page_table = (page_entry_t *)kmalloc(PAGE_TABLE_SIZE * sizeof(page_entry_t));
    for(uint32_t i = 0; i < PAGE_TABLE_SIZE; i++)
        page_table[i] = i*PAGE_ALIGN | PTE_BIT_PRESENT | PTE_BIT_READ_WRITE;
    return page_table;
}

void config_paging() {
    create_page_directory();
    page_entry_t *page_table = create_page_table();

    page_directory[0] = (page_entry_t)page_table | PTE_BIT_PRESENT | PTE_BIT_READ_WRITE;

    load_directory(page_directory);
    enable_paging();
}
