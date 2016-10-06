#ifndef PIT_H
#define PIT_H

#define     PIT_FREQ            1193180

#define     PIT_WRITE_LSB_MSB       0x30
#define     PIT_WRITE_COUNTER_0     0x00
#define     PIT_BINARY_MODE         0x00
#define     PIT_SQUARE_WAVE_MODE    0x06

void pit_init();
unsigned int pit_get_uptime();

#endif
