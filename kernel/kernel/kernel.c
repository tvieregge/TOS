#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/hal.h>
#include <kernel/shell.h>

void kernel_early(void)
{
    init_hal();
	terminal_initialize();
    init_shell("> ");
}

void kernel_main(void)
{
    for(;;);
}

