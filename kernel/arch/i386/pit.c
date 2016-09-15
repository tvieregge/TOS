#include "pit.h"
#include <stdint.h>

void PIT_irq_handler(struct regs* r) {
   static unsigned int ticks = 0;
   ticks += 1;
   printf("Tick: %d\n", ticks);
}

void PIT_init() {
    install_irq_handler(0, PIT_irq_handler);
}
