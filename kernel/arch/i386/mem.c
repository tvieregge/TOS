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
    
    // mem size is given in KiB
    uint32_t mem_size = (multiboot_info->mem_upper + multiboot_info->mem_lower)
                         * 1024;
    pm_num_blocks = mem_size / PM_BLOCK_SIZE;
    pm_map = &kernel_end;
    printf("num blocks: %d\n", (int)pm_num_blocks);
    printf("pm_map    : %d\n", (int)pm_map);
    printf("num bytes : %d\n", (int)(pm_num_blocks / PM_BLOCKS_PER_BYTE));
    pm_map_end = (void *)((char*)pm_map + pm_num_blocks/PM_BLOCKS_PER_BYTE);

    // everything starts off in use
    memset(pm_map, 0xff, pm_num_blocks / PM_BLOCKS_PER_BYTE);

    // clear everyhitn after the kernel/pm_map
    printf("ms - pmme = %d\n", mem_size-(uint32_t)pm_map_end);
    pm_clear_range(pm_map_end, mem_size-(uint32_t)pm_map_end);

    pm_test();
}

// Should these force block allignment?
//
// sets [start, end]
// If you specify an non aligned address it will set it
void pm_set_range(void *start, uint32_t size) {
    uint32_t start_bit = (uint32_t)start / PM_BLOCK_SIZE;
    uint32_t num_blocks = size / PM_BLOCK_SIZE;

    // round up to include possible last block
    if(size % PM_BLOCK_SIZE != 0) {
        num_blocks += 1;
    }

    // TODO: check to make sure we don't go out of bounds
    while(num_blocks > 0) {
        pm_set(start_bit);
        start_bit += 1;
        num_blocks -= 1;
    }
}

// clears (start, end)
// If you specify an non aligned address it will not set it
void pm_clear_range(void *start, uint32_t size) {
    uint32_t start_bit = (uint32_t)start / PM_BLOCK_SIZE;
    uint32_t num_blocks = size / PM_BLOCK_SIZE;

    // set possible first block
    if((uint32_t)start % PM_BLOCK_SIZE != 0) {
        start_bit += 1;
    }

    printf("clear num blocks: %d\n", num_blocks);
    // TODO: check to make sure we don't go out of bounds
    while(num_blocks > 0) {
        pm_clear(start_bit);
        start_bit += 1;
        num_blocks -= 1;
    }
}

void pm_set(uint32_t bit) {
    pm_map[bit/32] |= (1 << (bit % 32));
}

void pm_clear(uint32_t bit) {
    pm_map[bit/32] &= ~(1 << (bit % 32));
}

bool pm_test_bit(uint32_t bit) {
    return pm_map[bit/32] & (1 << (bit % 32));
}

void pm_test(void) {
    printf("kernel end: %d\n", (int)&kernel_end);
    printf("pm map end: %d\n", (int)pm_map_end);
    pm_map_print();
}

// prints the 1st mb of allocatable memory
void pm_map_print() {
    int width = 16;
    int height = 32;

    for(int i=0; i < width*height; ++i) {
        if(i % width == 0 && i != 0) {
            printf("\n");
        }
        printf("%d ", (int)pm_test_bit(i));
    }
    printf("\n");

}
