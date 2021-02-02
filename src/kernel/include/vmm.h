#ifndef VMM_H
#define VMM_H

#include "pmm.h"
#include "paging.h"
#include "../../Include/stdint.h"
#include "../../Include/stdbool.h"

typedef uint32_t virtual_addr_t;

myBool vmm_get_free_page(page_entry_t *e);
void vmm_map_page(void *virt, void *phy);
void vmm_free_page(page_entry_t *e);

#endif