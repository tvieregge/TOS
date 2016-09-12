#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "idt.h"
#include <kernel/hal.h>

int idt_initialize (uint16_t codeSel) {
	//set up idtr for processor
	_idtr.limit = sizeof (struct idt_descriptor) * I86_MAX_INTERRUPTS -1;
	_idtr.base	= (uint32_t)&_idt[0];
 
	memset((void*)&_idt[0], 0, sizeof(struct idt_descriptor) * I86_MAX_INTERRUPTS-1);
    set_isrs (codeSel);
 
	//install our idt
	__asm__( "lidt (%0)" :: "m" (_idtr) );
 
	return 0;
}

// Installs the ISR into the idt array
int idt_set_entry (uint32_t i, uint16_t flags, uint16_t sel, void (*irq)()) {
 
	if (i > I86_MAX_INTERRUPTS) {
		return -1;
    }
 
	if (irq == NULL) {
		return -1;
    }
 
	//get base address of interrupt handler
	uint64_t		uiBase = (uint64_t)&(*irq);
 
	// store base address into idt
	_idt[i].baseLo		=	uiBase & 0xffff;
	_idt[i].baseHi		=	(uiBase >> 16) & 0xffff;
	_idt[i].reserved	=	0;
	_idt[i].flags		=	flags;
    _idt[i].sel		    =	sel;
 
	return	0;
}

