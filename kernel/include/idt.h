#ifndef IDT_H
#define IDT_H
#include <stdint.h>

// interrupt descriptor
struct idt_entry {
 
	// bits 0-16 of interrupt routine (ir) address
	uint16_t		base_lo;
 
	// code selector in gdt
	uint16_t		sel;
 
	// reserved, shold be 0
	uint8_t			reserved;
 
	// bit flags. Set with flags above
	uint8_t			flags;
 
	// bits 16-32 of ir address
	uint16_t		base_hi;
} __attribute__((packed));


// structure for the processors idtr register
struct idtr {
 
	// size of the interrupt descriptor table (idt)
	uint16_t		limit;
 
	// base address of idt
	uint32_t		base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;
#endif