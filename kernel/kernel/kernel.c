#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/hal.h>

void kernel_early(void)
{
    init_hal();
	terminal_initialize();
}

void kernel_main(void)
{
	printf("Hello, kernel World!\n");
}
