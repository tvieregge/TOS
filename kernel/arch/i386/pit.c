#include "pit.h"
#include <stdint.h>

#define     PIT_REG_COUNTER_0   0x40
#define     PIT_REG_COUNTER_1   0x41
#define     PIT_REG_COUNTER_2   0x42
#define     PIT_REG_COMMAND     0x43

static unsigned int _ticks = 0;

void pit_irq_handler(struct regs* r) {
    _ticks += 1;
}

unsigned int pit_get_uptime() {
    return _ticks;
}

void pit_set_phase(uint32_t hz) {
    int div = PIT_FREQ / hz;
    uint8_t ocw = PIT_WRITE_LSB_MSB | PIT_WRITE_COUNTER_0 |
                  PIT_BINARY_MODE   | PIT_SQUARE_WAVE_MODE;

    outb(PIT_REG_COMMAND, ocw);
    outb(PIT_REG_COUNTER_0, div & 0xFF);
    outb(PIT_REG_COUNTER_0, div >> 8);
}

void pit_init() {
    pit_set_phase(100);
    install_irq_handler(0, pit_irq_handler);
}
