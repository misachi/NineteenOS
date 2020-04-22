#include <idt.h>
#include <stdio.h>
#include <string.h>

void default_handler()
{
    print("\tUnhandled exception Error");
    while(1);
}

void idt_gate(uint8_t num, irq_handler irq, uint16_t sel, uint8_t flags)
{
    if (num > MAX_IDT_ENTRY)
        return;

    uint32_t irq_addr = (uint32_t)&(*irq);

    idt_entries[num].base_lo    = irq_addr & 0xffff;
    idt_entries[num].base_hi    = (irq_addr >> 16) & 0xffff;
    idt_entries[num].flags      = flags;
    idt_entries[num].sel        = sel;
    idt_entries[num].reserved   = 0;
}

void initialize_idt(uint16_t sel)
{
    idtp.base = (uint32_t)&idt_entries;
    idtp.limit = sizeof(struct idt_entry) * MAX_IDT_ENTRY - 1;

    // Set IDT blocks to 0
    memset64((uint64_t)&idt_entries[0], 0, sizeof(struct idt_entry)*MAX_IDT_ENTRY);

    // Set all entries to the default handler above
    for (uint16_t i = 0; i < MAX_IDT_ENTRY; i++)
    {
        idt_gate(i, (irq_handler)default_handler, sel, FLAG);
    }
    install_idt();
}
