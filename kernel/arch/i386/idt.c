#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "idt.h"

int i86_idt_initialize (uint16_t codeSel) {
 
	//set up idtr for processor
	_idtr.limit = sizeof (struct idt_descriptor) * I86_MAX_INTERRUPTS -1;
	_idtr.base	= (uint32_t)&_idt[0];
 
	//null out the idt
	memset((void*)&_idt[0], 0, sizeof(struct idt_descriptor) * I86_MAX_INTERRUPTS-1);
 
	//register default handlers
	for (int i=0; i<I86_MAX_INTERRUPTS; i++)
		i86_install_handler (i, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32,
			codeSel, default_handler);
 
	//install our idt
	__asm__( "lidt (%0)" :: "m" (_idtr) );
 
	return 0;
}

//installs a new interrupt handler
int i86_install_handler (uint32_t i, uint16_t flags, uint16_t sel, void (*irq)()) {
 
	if (i>I86_MAX_INTERRUPTS) {
		return -1;
    }
 
	if (!irq) {
		return 0;
    }
 
	//get base address of interrupt handler
	uint64_t		uiBase = (uint64_t)&(*irq);
 
	//! store base address into idt
	_idt[i].baseLo		=	uiBase & 0xffff;
	_idt[i].baseHi		=	(uiBase >> 16) & 0xffff;
	_idt[i].reserved	=	0;
	_idt[i].flags		=	flags;
	_idt[i].sel		=	sel;
 
	return	0;
}

void default_handler() {
	printf("Default handler!\n");
	while(1) {;}
}
