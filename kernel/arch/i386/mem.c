#include <stdint.h>
#include <stdio.h>

#include "mem.h"

#define PM_BLOCK_SIZE   4096
#define KiB             1024
#define PM_BLOCKS_PER_BYTE  8

// NULL doesn't work outside of functions?
static uint32_t *pm_map = 0;
static uint32_t pm_num_blocks = 0;
static void *pm_map_end = 0;

void pm_map_init(multiboot_info_t *multiboot_info) {
    
    // ignore the first MB
    // mem_upper is given in KiB
    pm_num_blocks = multiboot_info->mem_upper / ( PM_BLOCK_SIZE/KiB );
    pm_map = &kernel_end;
    printf("num blocks: %d\n", pm_num_blocks);
    printf("pm_map   : %d\n", (int)pm_map);
    printf("num bytes : %d\n", pm_num_blocks/PM_BLOCKS_PER_BYTE);
    pm_map_end = (void *)((char*)pm_map + pm_num_blocks/PM_BLOCKS_PER_BYTE);
    pm_test();
}

void pm_test(void) {
    printf("kernel end: %d\n", (int)&kernel_end);
    printf("pm map end: %d\n", (int)pm_map_end);
}
