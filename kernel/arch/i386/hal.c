#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "kb.h"

int init_hal() {
    __asm__( "cli" );

    int ret_val;

	idt_initialize(0x8);

	ret_val = i86_init_gdt();
    if (ret_val != 0) {
        return -2;
    }

    PIC_init();
    PIT_init();

    KB_init();

    __asm__( "sti" );

    return 0;
}

unsigned int timer_get_uptime() {
    return PIT_get_uptime();
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
