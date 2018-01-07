/* 
 * A very simple event driven shell for testing commands.
 * To be completely redone once it becomes more usefull (when
 * programs can be loaded.
 */

#include <kernel/shell.h>
#include <kernel/tty.h>
#include <kernel/kernel.h>
#include <kernel/hal.h>
#include <stdio.h>

#include "string.h"
#include "shell_internal.h"

static char* _prompt = '\0';

char* _title = 
"  __________  _____  \n\
 /_  __/ __ \\/ ___/ \n\
  / / / / / /\\__ \\ \n\
 / / / /_/ /___/ /   \n\
/_/  \\____//____/";
 

char *commands[] = {
    "help",
    "uptime"
};

void init_shell(char* prompt) {
    _prompt = prompt;
    shell_test();
    printf("%s\n", _title);
    printf("%s", _prompt);
}

// For sending a char to the shell
void shell_send_char(const char c) {
    /*if(c == '\n') {
        run_cmd(shell_get_cmd(line));
    }
    else {
        shell_add_char(c);
    }*/
}
