#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "idt.h"

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

void isr_common_stub();

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
	isr_set (1, FLAGS, codeSel, _isr1);
	isr_set (2, FLAGS, codeSel, _isr2);
	isr_set (3, FLAGS, codeSel, _isr3);
	isr_set (4, FLAGS, codeSel, _isr4);
	isr_set (5, FLAGS, codeSel, _isr5);
	isr_set (6, FLAGS, codeSel, _isr6);
	isr_set (7, FLAGS, codeSel, _isr7);
	isr_set (8, FLAGS, codeSel, _isr8);
	isr_set (9, FLAGS, codeSel, _isr9);
	isr_set (10, FLAGS, codeSel, _isr10);
	isr_set (11, FLAGS, codeSel, _isr11);
	isr_set (12, FLAGS, codeSel, _isr12);
	isr_set (13, FLAGS, codeSel, _isr13);
	isr_set (14, FLAGS, codeSel, _isr14);
	isr_set (15, FLAGS, codeSel, _isr15);
	isr_set (16, FLAGS, codeSel, _isr16);
	isr_set (17, FLAGS, codeSel, _isr17);
	isr_set (18, FLAGS, codeSel, _isr18);
	isr_set (19, FLAGS, codeSel, _isr19);
	isr_set (20, FLAGS, codeSel, _isr20);
	isr_set (21, FLAGS, codeSel, _isr21);
	isr_set (22, FLAGS, codeSel, _isr22);
	isr_set (23, FLAGS, codeSel, _isr23);
	isr_set (24, FLAGS, codeSel, _isr24);
	isr_set (25, FLAGS, codeSel, _isr25);
	isr_set (26, FLAGS, codeSel, _isr26);
	isr_set (27, FLAGS, codeSel, _isr27);
	isr_set (28, FLAGS, codeSel, _isr28);
	isr_set (29, FLAGS, codeSel, _isr29);
	isr_set (30, FLAGS, codeSel, _isr30);
	isr_set (31, FLAGS, codeSel, _isr31);
}

// Installs the ISRs into the idt array
int isr_set (uint32_t i, uint16_t flags, uint16_t sel, void (*irq)()) {
 
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

void fault_handler() {
	printf("Fault handler!\n");
	while(1) {;}
}

void irq_handler() {
	printf("Fault handler!\n");
	while(1) {;}
}
