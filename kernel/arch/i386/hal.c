/*
 * The implementation of the Hardware Abstraction Layer.
 * This will include all the hardware specific functions
 * available.
 *
 * This will liekly be radically changed as the OS evolves
 */

#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "kb.h"
#include <kernel/hal.h>

int init_hal() {

    irq_disable();

	idt_init(GDT_CODE_SEL_1);
	gdt_init();
    pic_init();
    pit_init();
    kb_init();

    irq_enable();
    return 0;
}

unsigned int timer_get_uptime() {
    return pit_get_uptime();
}

void irq_disable() {
    __asm__( "cli" );
}

void irq_enable() {
    __asm__( "sti" );
}

// outb/inb from OSDev wiki
void outb(uint16_t port, uint8_t val) {
        __asm__ volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
        /* There's an outb %al, $imm8  encoding, for compile-time constant
         * port numbers that fit in 8b.  (N constraint).
         * Wider immediate constants would be truncated at assemble-time
         * (e.g. "i" constraint).
         * The  outb  %al, %dx  encoding is the only option for all other cases.
         * %1 expands to %dx because  port  is a uint16_t.  %w1 could be
         * used if we had the port number a wider C type */
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ( "inb %1, %0"
                     : "=a"(ret)
                     : "Nd"(port) );
    return ret;
}
