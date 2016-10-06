#ifndef PANIC_H
#define PANIC_H

// You should call this one, although it will get replaced with the below
void kpanic(const char* msg);

// not to be directly used
void kpanic_with_called(const char* msg, const char* caller);

#define kpanic(x) kpanic_with_called(x, __func__)

#endif
