/*
 * This file has everything involved the ISRsv(Interrupt Service Routines)
 * Mainly installing, uninstalling and calling the correct C function
 */

#ifndef ISR_H
#define ISR_H

#include <stdint.h>

// Tells the functiones called from the isrs what the stack looks like
// TODO: This is temporary, should be simplified
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss; /* pushed by the proc automatically */
};

typedef void (*isr_handler_routine)(struct regs* r);

void fault_handler();
void install_irq_handler(int i, isr_handler_routine irq_handler);
void uninstall_irq_handler(int i);

#endif
