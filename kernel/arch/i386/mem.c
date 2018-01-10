#include "mem.h"
#include <stdint.h>

long unsigned int MEM_SIZE_PHYSICAL = 0;

//note: regparm(3) avoids stack issues with gcc in real mode
void __attribute__((noinline)) __attribute__((regparm(3)))
detect_physical_memory() {
    
    uint32_t SMAP = 0x534D4150;
    SMAP_entry_t cur_entry = {};
    uint32_t int_signature, entry_bytes;
    int entries = 0;
    int cont_pos = 0;

    do {
        __asm__ volatile ( "int $0x15"
                         : "=a"(int_signature), "=b"(cont_pos), "=c"(entry_bytes)
                         : "a"(0xE820), "b"(cont_pos), "c"(sizeof(SMAP_entry_t)),
                           "d"(SMAP), "D"(&cur_entry));
        
        if(int_signature != SMAP) {
            break;
        }

        if (entry_bytes > 20 && (cur_entry.unsupported_ACPI & 0x0001) == 0) {
            // entry involves ACPI, ignore
        }
        else {
            entries += 1;
            MEM_SIZE_PHYSICAL += cur_entry.length;
        }

    } while (cont_pos != 0);
}
