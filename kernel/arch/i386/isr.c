#include "isr.h"
#include "pic.h"
#include <stddef.h>
#include <kernel/panic.h>
#include <stdio.h>

isr_handler_routine irq_handlers[PIC_NUM_INTERRUPTS] = {0}; 

void isr_handler(struct regs* r) {
    kpanic("exception received");
}

void install_irq_handler(int i, isr_handler_routine irq_handler) {
    irq_handlers[i] = irq_handler;
}

void uninstall_irq_handler(int i) {
    irq_handlers[i] = NULL;
}

void irq_server(struct regs* r) {
    void (*irq_handler)(struct regs* r);
    int irq_num = r->int_no - 32;
	irq_handler = irq_handlers[irq_num];
    
    if(irq_handler != NULL) {
        irq_handler(r);
    }

    if (r->int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}
