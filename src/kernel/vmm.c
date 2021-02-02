#include "./include/pmm.h"
#include "./include/vmm.h"

#include "include/paging.h"
#include "../Include/stdint.h"
#include "../Include/stdbool.h"

myBool vmm_alloc_page(page_entry_t *e) {
    physical_addr_t *phy = kmalloc(1);
    if (!phy)
        return myFalse;
    set_entry_bit(e, PTE_BIT_PRESENT);
    set_entry_physical_addr(e, (physical_addr_t)phy);
    return myTrue;
}

void vmm_free_page(page_entry_t *e) {
    physical_addr_t *phy = (physical_addr_t *)get_entry_physical_addr(*e);
    free(phy);
    unset_entry_bit(e, PTE_BIT_PRESENT);
}

void vmm_map_page(void *virt, void *phy) {
    page_directory_t *dir = get_page_directory();
    page_table_t *tbl = &dir[get_page_directory_idx((virtual_addr_t)virt)];
    if ((*tbl & PDE_BIT_PRESENT) != PDE_BIT_PRESENT) {
        tbl = create_page_table();
        set_entry_bit(tbl, PTE_BIT_PRESENT);
        set_entry_bit(tbl, PTE_BIT_READ_WRITE);
        set_entry_physical_addr(&dir[get_page_table_idx((virtual_addr_t)virt)], (page_table_t)tbl);
    }
    page_table_t *ptable = (page_table_t*)get_page_physical_addr(*tbl);
    page_entry_t *page = &ptable[get_page_table_idx((virtual_addr_t)virt)];
    set_entry_bit(page, PTE_BIT_PRESENT);
    set_entry_bit(page, PTE_BIT_READ_WRITE);
    set_entry_physical_addr(page, (page_table_t)phy);
}
