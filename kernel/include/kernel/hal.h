#ifndef _HAL_H
#define _HAL_H

#include <stdint.h>
#include <kernel/multiboot.h>

int init_hal(multiboot_info_t *multiboot_info);

unsigned int timer_get_uptime();

void irq_disable();
void irq_enable();

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

#endif
