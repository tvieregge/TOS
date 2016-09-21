#ifndef SHELL_H
#define SHELL_H

// A super simple command prompt for kernel space testing

void shell_send_char(const char c);
void init_shell(const char* prompt);

#endif
