#include <stdio.h>
#include <stdlib.h>

void __assert(char *ex, char *file, int line) {
    printf("assertion failed: %s\nline %s:%d\n", ex, file, line);
    abort();
}

