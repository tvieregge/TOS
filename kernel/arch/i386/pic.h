/*
 * The functions pertaining to the PIC (Programmable 
 * Interrupt Controller). Mostly setup
 */

#ifndef PIC_H
#define PIC_H

#define PIC_NUM_INTERRUPTS 16

void pic_init();
void pic_eoi(unsigned int int_no);

#endif
