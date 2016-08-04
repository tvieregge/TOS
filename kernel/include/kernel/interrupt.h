#ifndef _INTURRUPT_H
#define _INTURRUPT_H

#define MAX_DESCRIPTORS 1024

struct __attribute__((__packed__)) gdtr {
 
	//! size of gdt
	uint16_t		m_limit;
 
	//! base address of gdt
	uint32_t		m_base;
};

// gdt descriptor. A gdt descriptor defines the properties of a specific
// memory block and permissions.
 
struct gdt_descriptor {
 
	//! bits 0-15 of segment limit
	uint16_t		limit;
 
	//! bits 0-23 of base address
	uint16_t		baseLo;
	uint8_t			baseMid;
 
	//! descriptor bit flags. Set using bit masks above
	uint16_t		flags;
 
	//! bits 24-32 of base address
	uint8_t			baseHi;
};

int init_gdt();
void reload_segments();

#endif
