#ifndef _HAL_H
#define _HAL_H

#include <stdint.h>
int init_hal();

unsigned int timer_get_uptime();

void irq_disable();
void irq_enable();

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

#endif
