#include <kernel/shell.h>
#include <kernel/tty.h>

#include "string.h"

static char* _prompt = '\0';

char const * const _title[] = {
"  __________  _____",
" /_  __/ __ \\/ ___/",
"  / / / / / /\\__ \\ ",
" / / / /_/ /___/ / ",
"/_/  \\____//____/"
}; 

char* commands[] = {
    "help",
    "uptime"
};

void cmd_help() {
    int num_commands = (sizeof commands) / (sizeof commands[0]);
    printf("Commands are:");
    for(int i=0; i<num_commands; ++i) {
        printf("\n%s", commands[i]);
    }
}

void cmd_time() {
    unsigned int ticks = timer_get_uptime();
    printf("Uptime: %d ticks", ticks);
}

void process_cmd(char *cmd) {
    if(memcmp(commands[0], cmd, strlen(commands[0])+1) == 0) {
        cmd_help();
    }
    else if(memcmp(commands[1], cmd, strlen(commands[0])+1) == 0) {
        cmd_time();
    }
    else if(memcmp('\n', cmd, 1) == 0) {}
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
        cur_input_index -= 1;
        putchar(c);
    }
    else
    {
        current_input[cur_input_index] = c;
        cur_input_index += 1;
        putchar(c);
    }
}

void init_shell(const char* prompt) {
    int title_len = sizeof(_title)/sizeof(_title[0]);
    _prompt = prompt;

    for(int i=0; i<title_len; i++) {
        printf("%s\n", _title[i]);
    }
    printf("%s", _prompt);
}
