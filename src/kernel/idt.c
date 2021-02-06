#include "./include/pic.h"
#include "./include/idt.h"
#include "../Include/string.h"
#include "../Include/stdio.h"

// Load our IDT
static void inline install_idt(void){
	__asm__ volatile("lidt %0" :: "m" (idtp));
}

void default_handler()
{
    print("\tUnhandled exception Error!!!");
    while(1);
}

void idt_gate(uint8_t num, irq_handler irq, uint16_t sel, uint8_t flags)
{
    if (num > MAX_IDT_ENTRY)
        return;

    uint32_t irq_addr = (uint32_t)&(*irq);

    IDT[num].base_lo    = irq_addr & 0xffff;
    IDT[num].base_hi    = (irq_addr >> 16) & 0xffff;
    IDT[num].flags      = flags;
    IDT[num].sel        = sel;
    IDT[num].reserved   = 0;
}

void initialize_idt(uint16_t sel)
{
    i86_initialize_pic();
    idtp.base = (uint32_t)&IDT;
    idtp.limit = sizeof(struct idt_entry) * MAX_IDT_ENTRY - 1;

    // Set IDT blocks to 0
    memset((uint64_t *)&IDT[0], 0, sizeof(struct idt_entry)*MAX_IDT_ENTRY);

    // Set all entries to the default handler above
    for (uint16_t i = 0; i < MAX_IDT_ENTRY; i++)
    {
        idt_gate(i, (irq_handler)default_handler, sel, FLAG);
    }
    install_idt();
}
