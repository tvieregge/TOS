/*
 *  The entry point and main loop for the kernel
 */

#ifndef KERNEL_H
#define KERNEL_H

// Some basic defines for use in the kernel.
// Many (all?) can be moved out when there's a user space.

#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
       _a > _b ? _a : _b; })

#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
       _a < _b ? _a : _b; })

#endif
