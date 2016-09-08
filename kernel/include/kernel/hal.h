#ifndef _HAL_H
#define _HAL_H

int init_hal();

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port)

#endif
