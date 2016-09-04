#include "gdt.h"
#include "idt.h"

int init_hal() {
    __asm__( "cli" );

	ret_val = i86_idt_initialize(0x8);
    if (ret_val != 0) {
        return -1;
    }

	ret_val = i86_init_gdt();
    if (ret_val != 0) {
        return -2;
    }
}
