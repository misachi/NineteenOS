#include "include/pmm.h"
#include "include/paging.h"
#include "../Include/string.h"
#include "../Include/stdbool.h"

extern void load_directory(page_directory_t *directory);
extern void enable_paging();

static page_directory_t *page_directory = 0;

inline myBool is_page_aligned(page_entry_t e) {
    return e & PAGE_ALIGN_MASK;
}

inline void page_align_entry(page_entry_t *e) {
    *e = (*e + PAGE_ALIGN_MASK) & ~PAGE_ALIGN_MASK;
}

inline page_entry_t get_page_table_idx(uint32_t v_addr) {
    return (v_addr >> 12) & PAGE_ALIGN_MASK;
}

inline page_directory_t get_page_directory_idx(uint32_t v_addr) {
    return (v_addr >> 22) & PAGE_ALIGN_MASK;
}

inline physical_addr_t get_page_physical_addr(uint32_t v_addr) {
    return v_addr & PAGE_ALIGN_MASK;
}

inline void set_entry_bit(page_entry_t *e, page_entry_t bit) {
    *e |= bit;
}

inline void unset_entry_bit(page_entry_t *e, page_entry_t bit) {
    *e &= ~bit;
}

inline physical_addr_t get_entry_physical_addr(page_entry_t e) {
    return PTE_PHYS_ADR & e;
}

inline void set_entry_physical_addr(page_entry_t *e, uint32_t addr) {
    *e = (*e & ~PTE_PHYS_ADR) | addr;
}

page_directory_t *get_page_directory() {
    return page_directory;
}

void create_page_directory() {
    page_directory = (page_directory_t *)kmalloc(1);
    memset(page_directory, 0, PAGE_SIZE);

    for(page_directory_t i = 0; i < PAGE_DIRECTORY_SIZE; i++)
        set_entry_bit(&page_directory[i], PDE_BIT_READ_WRITE);
}

page_table_t *create_page_table() {
    page_table_t *page_table = kmalloc(1);
    memset(page_table, 0, PAGE_SIZE);

    // for(page_entry_t i = 0; i < PAGE_TABLE_SIZE; i++) {
    //     page_entry_t *e = 0;
    //     set_entry_bit(&page_table[i], PTE_BIT_PRESENT);
    //     set_entry_bit(&page_table[i], PTE_BIT_READ_WRITE);
    //     set_entry_physical_addr(&page_table[i], (page_entry_t)e);
    // }
    return page_table;
}

void config_paging() {
    create_page_directory();
    page_table_t *page_table = create_page_table();

    set_entry_bit(&page_directory[0], PDE_BIT_PRESENT);
    set_entry_bit(&page_directory[0], PDE_BIT_READ_WRITE);
    set_entry_physical_addr(&page_directory[0], (page_table_t)page_table);

    load_directory(&page_directory[0]);
    enable_paging();
}
