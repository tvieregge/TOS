#ifndef MEM_H
#define MEM_H

#include <kernel/multiboot.h>

extern void kernel_end;

void pm_map_init(multiboot_info_t *multiboot_info);
void pm_test(void);

#endif
