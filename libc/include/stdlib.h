#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

// Non portable temporary function from Brokenthorn OS tutorials
int temp_itoa(int i, unsigned int base, char* buf);

#ifdef __cplusplus
}
#endif

#endif
