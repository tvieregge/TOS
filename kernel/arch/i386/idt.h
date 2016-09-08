#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define I86_MAX_INTERRUPTS		256

//! must be in the format 0D110, where D is descriptor type
#define I86_IDT_DESC_BIT16		0x06	//00000110
#define I86_IDT_DESC_BIT32		0x0E	//00001110
#define I86_IDT_DESC_RING1		0x40	//01000000
#define I86_IDT_DESC_RING2		0x20	//00100000
#define I86_IDT_DESC_RING3		0x60	//01100000
#define I86_IDT_DESC_PRESENT	0x80	//10000000

struct __attribute__ ((__packed__)) idt_descriptor {
 
	//! bits 0-16 of interrupt routine (ir) address
	uint16_t		baseLo;
 
	//! code selector in gdt
	uint16_t		sel;
 
	//! reserved, shold be 0
	uint8_t			reserved;
 
	//! bit flags. Set with flags above
	uint8_t			flags;
 
	//! bits 16-32 of ir address
	uint16_t		baseHi;
};

struct __attribute__((__packed__)) idtr {
 
	//! size of gdt
	uint16_t		limit;
 
	//! base address of gdt
	uint32_t		base;
};

void fault_handler();
int idt_initialize (uint16_t codeSel);
int idt_set_entry (uint32_t i, uint16_t flags, uint16_t sel, void (*irq)());
int set_isrs(uint16_t codeSel);

// interrupt descriptor table
static struct idt_descriptor	_idt [I86_MAX_INTERRUPTS];
 
// idtr structure used to help define the cpu's idtr register
static struct idtr				_idtr;

// Tells the functiones called from the isrs what the stack looks like
// TODO: This is temporary, should be simplified
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss; /* pushed by the proc automatically */
};


#endif
