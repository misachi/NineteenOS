#ifndef _PAGING_H
#define _PAGING_H

#include "../../Include/stdint.h"
#include "../../Include/stdbool.h"
#include "pmm.h"

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
typedef uint32_t page_table_t;

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

extern myBool is_page_aligned(page_entry_t e);

extern void page_align_entry(page_entry_t *e);

extern page_entry_t get_page_table_idx(uint32_t v_addr);

extern page_directory_t get_page_directory_idx(uint32_t v_addr);

extern physical_addr_t get_page_physical_addr(uint32_t v_addr);

extern void set_entry_bit(page_entry_t *e, page_entry_t bit);

extern void unset_entry_bit(page_entry_t *e, page_entry_t bit);

extern physical_addr_t get_entry_physical_addr(page_entry_t e);

extern void set_entry_physical_addr(page_entry_t *e, uint32_t addr);

void create_page_directory();
page_entry_t *create_page_table();
void map_page_table(page_directory_t *pd, page_entry_t *e);
void config_paging();

page_directory_t *get_page_directory();
#endif
