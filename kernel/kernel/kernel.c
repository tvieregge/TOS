#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/interrupt.h>

void kernel_early(void)
{
	init_gdt();
	i86_idt_initialize(0x8);
	terminal_initialize();
	__asm__( "INT $5" );
}

void kernel_main(void)
{
	printf("Hello, kernel World!\n");
}
