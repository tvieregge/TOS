#ifndef MEM_H
#define MEM_H

#include <stdbool.h>
#include <stdint.h>
#include <kernel/multiboot.h>

extern uint32_t kernel_end;

void pm_map_init(multiboot_info_t *multiboot_info);
void pm_test(void);

void pm_set_range(void *start, uint32_t size);
void pm_clear_range(void *start, uint32_t size);

void pm_set(uint32_t bit);
void pm_clear(uint32_t bit);
bool pm_test_bit(uint32_t bit);
int32_t pm_get_free_bit(void);

void pm_map_print();

#endif
