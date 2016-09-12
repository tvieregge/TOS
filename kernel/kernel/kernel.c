#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/hal.h>

char* title[] = {
"  __________  _____",
" /_  __/ __ \\/ ___/",
"  / / / / / /\\__ \\ ",
" / / / /_/ /___/ / ",
"/_/  \\____//____/  "
}; 

void kernel_early(void)
{
    init_hal();
	terminal_initialize();
}

void kernel_main(void)
{
    int title_len = sizeof(title)/sizeof(title[0]);
    for(int i=0; i<title_len; i++) {
        printf(title[i]);
        printf("\n");
    }
    for(;;);
}

