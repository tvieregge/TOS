#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "idt.h"
#include <kernel/hal.h>

void _isr1();
void _isr2();
void _isr3();
void _isr4();
void _isr5();
void _isr6();
void _isr7();
void _isr8();
void _isr9();
void _isr10();
void _isr11();
void _isr12();
void _isr13();
void _isr14();
void _isr15();
void _isr16();
void _isr17();
void _isr18();
void _isr19();
void _isr20();
void _isr21();
void _isr22();
void _isr23();
void _isr24();
void _isr25();
void _isr26();
void _isr27();
void _isr28();
void _isr29();
void _isr30();
void _isr31();
void _isr32();

void _irq0();
void _irq1();
void _irq2(); 
void _irq3(); 
void _irq4(); 
void _irq5(); 
void _irq6(); 
void _irq7(); 
void _irq8(); 
void _irq9(); 
void _irq10(); 
void _irq11(); 
void _irq12(); 
void _irq13(); 
void _irq14(); 
void _irq15(); 

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

int set_isrs(uint16_t codeSel) {
    const int FLAGS = I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32;
	idt_set_entry (1, FLAGS, codeSel, _isr1);
	idt_set_entry (2, FLAGS, codeSel, _isr2);
	idt_set_entry (3, FLAGS, codeSel, _isr3);
	idt_set_entry (4, FLAGS, codeSel, _isr4);
	idt_set_entry (5, FLAGS, codeSel, _isr5);
	idt_set_entry (6, FLAGS, codeSel, _isr6);
	idt_set_entry (7, FLAGS, codeSel, _isr7);
	idt_set_entry (8, FLAGS, codeSel, _isr8);
	idt_set_entry (9, FLAGS, codeSel, _isr9);
	idt_set_entry (10, FLAGS, codeSel, _isr10);
	idt_set_entry (11, FLAGS, codeSel, _isr11);
	idt_set_entry (12, FLAGS, codeSel, _isr12);
	idt_set_entry (13, FLAGS, codeSel, _isr13);
	idt_set_entry (14, FLAGS, codeSel, _isr14);
	idt_set_entry (15, FLAGS, codeSel, _isr15);
	idt_set_entry (16, FLAGS, codeSel, _isr16);
	idt_set_entry (17, FLAGS, codeSel, _isr17);
	idt_set_entry (18, FLAGS, codeSel, _isr18);
	idt_set_entry (19, FLAGS, codeSel, _isr19);
	idt_set_entry (20, FLAGS, codeSel, _isr20);
	idt_set_entry (21, FLAGS, codeSel, _isr21);
	idt_set_entry (22, FLAGS, codeSel, _isr22);
	idt_set_entry (23, FLAGS, codeSel, _isr23);
	idt_set_entry (24, FLAGS, codeSel, _isr24);
	idt_set_entry (25, FLAGS, codeSel, _isr25);
	idt_set_entry (26, FLAGS, codeSel, _isr26);
	idt_set_entry (27, FLAGS, codeSel, _isr27);
	idt_set_entry (28, FLAGS, codeSel, _isr28);
	idt_set_entry (29, FLAGS, codeSel, _isr29);
	idt_set_entry (30, FLAGS, codeSel, _isr30);
	idt_set_entry (31, FLAGS, codeSel, _isr31);

	idt_set_entry (32, FLAGS, codeSel, _irq0);
	idt_set_entry (33, FLAGS, codeSel, _irq1);
	idt_set_entry (34, FLAGS, codeSel, _irq2);
	idt_set_entry (35, FLAGS, codeSel, _irq3);
	idt_set_entry (36, FLAGS, codeSel, _irq4);
	idt_set_entry (37, FLAGS, codeSel, _irq5);
	idt_set_entry (38, FLAGS, codeSel, _irq6);
	idt_set_entry (39, FLAGS, codeSel, _irq7);
	idt_set_entry (40, FLAGS, codeSel, _irq8);
	idt_set_entry (41, FLAGS, codeSel, _irq9);
	idt_set_entry (42, FLAGS, codeSel, _irq10);
	idt_set_entry (43, FLAGS, codeSel, _irq11);
	idt_set_entry (44, FLAGS, codeSel, _irq12);
	idt_set_entry (45, FLAGS, codeSel, _irq13);
	idt_set_entry (46, FLAGS, codeSel, _irq14);
	idt_set_entry (47, FLAGS, codeSel, _irq15);
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

void fault_handler(struct regs* r) {
    // Because printf isn't finished/understood
    int ascii_rep = r->int_no + 48;
	printf("Exception: ");
	printf(&ascii_rep);
	while(1) {;}
}

void irq_handler(struct regs* r) {
    int ascii_rep = r->int_no + 48;
	//printf("IRQ: ");
	//printf(&ascii_rep);
    //printf("\n");

    if (r->int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}
