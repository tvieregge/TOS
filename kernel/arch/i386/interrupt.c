#include <stdio.h>
#include <stdint.h>

#include <kernel/interrupt.h> 

static uint64_t gdt[MAX_DESCRIPTORS];
static struct   gdtr gdtr;

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s,
												     // g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0

	return descriptor;
}

int init_gdt() {
	// set up gdtr
	gdtr.m_limit = sizeof(uint64_t) * MAX_DESCRIPTORS-1;
	gdtr.m_base = (uint32_t)&gdt[0];

	gdt[0] = create_descriptor(0, 0, 0);	// set null descriptor
    gdt[1] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt[2] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt[3] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt[4] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

	__asm__( "lgdt (%0)" :: "m" (gdtr) );

	reload_segments();

	return 0;
}

//! initialize idt
int i86_idt_initialize (uint16_t codeSel) {
 
	//! set up idtr for processor
	_idtr.limit = sizeof (struct idt_descriptor) * I86_MAX_INTERRUPTS -1;
	_idtr.base	= (uint32_t)&_idt[0];
 
	//! null out the idt
	memset ((void*)&_idt[0], 0, sizeof (idt_descriptor) * I86_MAX_INTERRUPTS-1);
 
	//! register default handlers
	for (int i=0; i<I86_MAX_INTERRUPTS; i++)
		i86_install_ir (i, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32,
			codeSel, (I86_IRQ_HANDLER)i86_default_handler);
 
	//! install our idt
	__asm__( "lidt (%0)" :: "m" (idtr) );
 
	return 0;
}

//! installs a new interrupt handler
int i86_install_ir (uint32_t i, uint16_t flags, uint16_t sel, I86_IRQ_HANDLER irq) {
 
	if (i>I86_MAX_INTERRUPTS)
		return 0;
 
	if (!irq)
		return 0;
 
	//! get base address of interrupt handler
	uint64_t		uiBase = (uint64_t)&(*irq);
 
	//! store base address into idt
	_idt[i].baseLo		=	uiBase & 0xffff;
	_idt[i].baseHi		=	(uiBase >> 16) & 0xffff;
	_idt[i].reserved	=	0;
	_idt[i].flags		=	flags;
	_idt[i].sel		=	sel;
 
	return	0;
}
