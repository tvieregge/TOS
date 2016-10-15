/* 
 * A very simple event driven shell for testing commands.
 * To be completely redone once it becomes more usefull (when
 * programs can be loaded.
 */

#ifndef SHELL_H
#define SHELL_H

void shell_send_char(const char c);
void init_shell(const char* prompt);

#endif
