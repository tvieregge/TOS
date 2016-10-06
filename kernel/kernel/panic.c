#include <kernel/panic.h>

// kpanic is replaced with this function, with __func__ added
// for the second argument. See the macro in panic.h for details
void kpanic_with_called(const char* msg, const char* caller) {
    printf("EVERYBODY PANIC\n");
    printf("%s: %s\n", caller, msg);
    printf("Fatal error, please reboot");

    for(;;);
}
