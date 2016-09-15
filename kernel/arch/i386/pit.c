#include "pit.h"
#include <stdint.h>

#define     PIT_REG_COUNTER_0   0x40
#define     PIT_REG_COUNTER_1   0x41
#define     PIT_REG_COUNTER_2   0x42
#define     PIT_REG_COMMAND     0x43

void PIT_irq_handler(struct regs* r) {
    static unsigned int ticks = 0;
    ticks += 1;
    if(ticks % 100 == 0) {
        printf("One second, Tick: %d\n", ticks);
    }
}

void PIT_set_phase(uint32_t hz) {
    int div = PIT_FREQ / hz;
    uint8_t ocw = PIT_WRITE_LSB_MSB | PIT_WRITE_COUNTER_0 |
                  PIT_BINARY_MODE   | PIT_SQUARE_WAVE_MODE;

    outb(PIT_REG_COMMAND, ocw);
    outb(PIT_REG_COUNTER_0, div & 0xFF);
    outb(PIT_REG_COUNTER_0, div >> 8);
}

void PIT_init() {
    PIT_set_phase(100);
    install_irq_handler(0, PIT_irq_handler);
}
