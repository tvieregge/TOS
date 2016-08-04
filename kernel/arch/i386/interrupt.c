#include <stdio.h>
#include <stdint.h>

#include <kernel/interrupt.h> 

static uint64_t gdt[MAX_DESCRIPTORS];
static struct   gdtr gdtr;

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s,
												     // g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0

	return descriptor;
}

int init_gdt() {
	// set up gdtr
	gdtr.m_limit = sizeof(uint64_t) * MAX_DESCRIPTORS-1;
	gdtr.m_base = (uint32_t)&gdt[0];

	gdt[0] = create_descriptor(0, 0, 0);
	/*gdt[1] = create_descriptor(0, 0xFFFFFFFF, 0x9A);
	gdt[2] = create_descriptor(0, 0xFFFFFFFF, 0x92);*/
    gdt[1] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt[2] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt[3] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt[4] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

	/*// Selector 0x00 cannot be used
	gdt[0].base=0;
	gdt[0].limit=0;
	gdt[0].flags=0;
	
	// Selector 0x08 will be our code
	gdt[1].base=0;
	gdt[1].limit=0xffffffff;
	gdt[1].flags=0x9A;
	
	// Selector 0x10 will be our data
	gdt[2].base=0;
	gdt[2].limit=0xffffffff;
	gdt[2].flags=0x92;*/         

	__asm__( "lgdt (%0)" :: "m" (gdtr) );

	reload_segments();

	return 0;
}
