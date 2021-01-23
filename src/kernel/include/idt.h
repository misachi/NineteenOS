#ifndef IDT_H
#define IDT_H
#include "../../Include/stdint.h"

#define MAX_IDT_ENTRY 256
#define FLAG 0x8E

// interrupt descriptor
struct idt_entry {
 
	// bits 0-16 of interrupt routine address
	uint16_t		base_lo;
 
	// code selector in gdt
	uint16_t		sel;
 
	// Always 0
	uint8_t			reserved;
 
	// bit flags
	uint8_t			flags;
 
	// bits 16-32 of interrupt routine address
	uint16_t		base_hi;
} __attribute__((packed));

typedef void (*irq_handler)();

struct idtr {
 
	// size of the idt
	uint16_t		limit;
 
	// base address of idt
	uint32_t		base;
} __attribute__((packed));

struct idt_entry IDT[256];

// Our IDT pointer register
struct idtr idtp;

// Load our IDT
static void inline install_idt(void){
	__asm__ volatile("lidt %0" :: "m" (idtp));
}

void idt_gate(uint8_t num, irq_handler irq, uint16_t sel, uint8_t flags);

// Our default Interrupt Routine(in case NONE is provided)
void default_handler();
void initialize_idt(uint16_t sel);
#endif