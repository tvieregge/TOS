#include <kernel/multiboot.h>
#include <stdint.h>

extern  void* kernel_end;

void pm_map_init(multiboot_info_t *multiboot_info) {
#include <stdio.h>
    printf("kernel end: %d\n", (int)&kernel_end);
}
