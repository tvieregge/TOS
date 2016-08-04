#include <stdio.h>
#include <stdint.h>

#include <kernel/interrupt.h> 

static struct gdt_descriptor gdt[MAX_DESCRIPTORS];
static struct gdtr	     gdtr;

int init_gdt() {
	// set up gdtr
	gdtr.m_limit = (sizeof (struct gdt_descriptor) * MAX_DESCRIPTORS)-1;
	gdtr.m_base = (uint32_t)&gdt[0];


	/*****************************
	*	
	*   NEED TO ENCODE PROPERLY    (granularity)
	*
	******************************/


	// Selector 0x00 cannot be used
	gdt[0].baseLo=0; gdt[0].baseMid=0; gdt[0].limit=0; gdt[0].flags=0;
	// Selector 0x08 will be our code
	//gdt[1].baseLo=0; gdt[1].baseMid=0; gdt[1].limit=0xffffffff; gdt[1].flags=0x9A;
	// Selector 0x10 will be our data
	//gdt[2].baseLo=0; gdt[2].baseMid=0; gdt[2].limit=0xffffffff; gdt[2].flags=0x92;         

	asm( "lgdt (%0)" :: "m" (gdtr) );

        reload_segments();

	return 0;
}
