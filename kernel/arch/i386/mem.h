#include <stdint.h>

extern long unsigned int MEM_SIZE_PHYSICAL;

typedef struct SMAP_entry {

	uint64_t base;      // base address uint64_t
	uint64_t length;    // length uint64_t
	uint32_t type;          // entry Type
	uint32_t unsupported_ACPI; // extended

}__attribute__((packed)) SMAP_entry_t;

