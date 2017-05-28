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

void cmd_help() {
    int num_commands = (sizeof commands) / (sizeof commands[0]);

    printf("%s", "Commands are:");
    for(int i=0; i<num_commands; ++i) {
        printf("\n%s", commands[i]);
    }
}

void cmd_time() {
    unsigned int ticks = timer_get_uptime();

    printf("Uptime: %d ticks", ticks);
}

int compare_cmd(const char *unknown, const char *known) {
    size_t min;

    min = min(strlen(known), strlen(unknown));
    return memcmp(known, unknown, min+1);
}

void process_cmd(char *cmd) {

    if(compare_cmd(cmd, commands[0]) == 0) {
        cmd_help();
    }
    else if(compare_cmd(cmd, commands[1]) == 0) {
        cmd_time();
    }
    else if(compare_cmd(cmd, "") == 0) {
        // empty command
    }
    else {
        printf("Unrecognized input");
    }
}

// For sending a char to the shell
void shell_send_char(const char c) {
    static char         current_input[32];
    static unsigned int cur_input_index = 0;
    
    if(c == '\n') {
        current_input[cur_input_index] = '\0';
        printf("\n");
        process_cmd(current_input);
        cur_input_index = 0;
        printf("\n%s", _prompt);
    }
    else if(c == '\b') {
        if(cur_input_index == 0) {
        }
        else {
            cur_input_index -= 1;
        }
        putchar(c);
    }
    else
    {
        current_input[cur_input_index] = c;
        cur_input_index += 1;
        putchar(c);
    }
}

void init_shell(char* prompt) {
    _prompt = prompt;
    printf("%s\n", _title);
    printf("%s", _prompt);
}
