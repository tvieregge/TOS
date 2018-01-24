/*
 *  The entry point and main loop for the kernel
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/hal.h>
#include <kernel/shell.h>

#include <kernel/multiboot.h>

void kernel_early(multiboot_info_t* mbd, unsigned int magic)
{
	terminal_initialize(); // needed first for debug output
    init_hal(mbd);

    printf("mem upper size: %d\n", (int)mbd->mem_upper);

    init_shell("> ");
}

void kernel_main(void)
{
    for(;;);
}

