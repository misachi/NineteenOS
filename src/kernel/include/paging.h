#ifndef _PAGING_H
#define _PAGING_H

#include "../../Include/stdint.h"

#define PAGE_ALIGN 4096
#define PAGE_ALIGN_MASK (PAGE_ALIGN - 1)

#define PAGE_TABLE_SIZE   1024
#define PAGE_DIRECTORY_SIZE 1024

/* Page Table Entry */
enum {
    PTE_BIT_PRESENT                     = 1,
    PTE_BIT_READ_WRITE                  = 2,
    PTE_BIT_USER_SUPERVISOR             = 4,
    PTE_BIT_WRITE_THROUGH               = 8,
    PTE_BIT_CACHE_DISABLE               = 0x10,
    PTE_BIT_ACCESSED                    = 0x20,
    PTE_BIT_DIRTY                       = 0x40,
    PTE_BIT_PAT                         = 0x80,
    PTE_GLOBAL                          = 0x100,
    PTE_IGNORED                         = 0x200,
    PTE_PHYS_ADR                        = 0x7ffff000
};

typedef uint32_t page_entry_t;

/* Page Directory Entry */
enum {
    PDE_BIT_PRESENT                     = 1,
    PDE_BIT_READ_WRITE                  = 2,
    PDE_BIT_USER_SUPERVISOR             = 4,
    PDE_BIT_WRITE_THROUGH               = 8,
    PDE_BIT_CACHE_DISABLE               = 0x10,
    PDE_BIT_ACCESSED                    = 0x20,
    PDE_BIT_IGNORED                     = 0x40,
    PDE_BIT_PS                          = 0x80,
    PDE_GLOBAL                          = 0x100,
    PDE_IGNORED                         = 0x200,
    PDE_PHYS_ADR                        = 0x7ffff000
};

typedef uint32_t page_directory_t;

inline uint8_t is_page_aligned(page_entry_t e) {
    return e & PAGE_ALIGN_MASK;
}

inline void page_align_entry(page_entry_t *e) {
    *e = (*e + PAGE_ALIGN_MASK) & ~PAGE_ALIGN_MASK;
}

inline page_entry_t get_page_table_idx(uint32_t v_addr) {
    return (v_addr >> 12) & 1023;
}

inline page_directory_t get_page_directory_idx(uint32_t v_addr) {
    return (v_addr >> 22) & 1023;
}

inline uint32_t get_page_physical_addr(uint32_t v_addr) {
    return v_addr & PAGE_ALIGN_MASK;
}

inline void set_entry_bit(page_entry_t *e, page_entry_t bit) {
    *e |= bit;
}

inline void unset_entry_bit(page_entry_t *e, page_entry_t bit) {
    *e &= ~bit;
}

inline page_entry_t get_entry_physical_addr(page_entry_t e) {
    return PTE_PHYS_ADR & e;
}

inline void set_entry_physical_addr(page_entry_t *e, uint32_t addr) {
    *e = (*e << 12) | addr;
}

void create_page_directory();
page_entry_t *create_page_table();
void config_paging();

page_entry_t *get_page_table(uint32_t addr);
page_directory_t *get_page_directory(uint32_t addr);

#endif
