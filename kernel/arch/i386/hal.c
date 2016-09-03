#include "gdt.h"
#include "idt.h"

int init_hal() {
    __asm__( "cli" );
	i86_idt_initialize(0x8);
	i86_init_gdt();
}
