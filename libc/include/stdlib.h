#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

#define assert(ex) ((ex) ? : __assert(#ex, __FILE__, __LINE__))
__attribute__((__noreturn__))
void __assert(char *ex, char *fi1le, int line);

// Non portable temporary function from Brokenthorn OS tutorials
int temp_itoa(int i, unsigned int base, char* buf);

#ifdef __cplusplus
}
#endif

#endif
