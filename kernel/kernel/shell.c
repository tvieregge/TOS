#include <kernel/shell.h>
#include <kernel/tty.h>

<<<<<<< 23c71b83de8013eb3f120818ea855563bfe29884
=======
#include "string.h"

static char* _prompt = '\0';
>>>>>>> strange stuff with git. Done first draft of shell
char const * const title[] = {
"  __________  _____",
" /_  __/ __ \\/ ___/",
"  / / / / / /\\__ \\ ",
" / / / /_/ /___/ / ",
"/_/  \\____//____/"
}; 

char* commands[] = {
    "help",
<<<<<<< 23c71b83de8013eb3f120818ea855563bfe29884
    "time"
};

void process_cmd() {

}

=======
    "uptime"
};

void cmd_help() {
    int num_commands = (sizeof commands) / (sizeof commands[0]);
    printf("Commands are:\n ");
    for(int i=0; i<num_commands; ++i) {
        printf("              %s\n", commands[i]);
    }
}

void cmd_time() {
    unsigned int ticks = timer_get_uptime();
    printf("Uptime: %d ticks", ticks);
}

void process_cmd(char *cmd) {
    if(memcmp(commands[0], cmd, strlen(commands[0])) == 0) {
        cmd_help();
    }
    else if(memcmp(commands[1], cmd, strlen(commands[1])) == 0) {
        cmd_time();
    }
    else if(memcmp('\n', cmd, 1) == 0) {}
    else {
        printf("Unrecognized input");
    }
}

// For sending a char to the shell
>>>>>>> strange stuff with git. Done first draft of shell
void shell_send_char(const char c) {
    static char current_input[32];
    static unsigned int cur_input_index = 0;

    if(c == '\n') {
        current_input[cur_input_index] = '\0';
<<<<<<< 23c71b83de8013eb3f120818ea855563bfe29884
        process_cmd();
    }
    current_input[cur_input_index] = c;
    cur_input_index += 1;
    putchar(c);
=======
        
        printf("\n");
        process_cmd(current_input);
        cur_input_index = 0;
        printf("\n%s", _prompt);
    }
    else
    {
        current_input[cur_input_index] = c;
        cur_input_index += 1;
        putchar(c);
    }
>>>>>>> strange stuff with git. Done first draft of shell
}

void init_shell(const char* prompt) {
    int title_len = sizeof(title)/sizeof(title[0]);
<<<<<<< 23c71b83de8013eb3f120818ea855563bfe29884
=======
    _prompt = prompt;
>>>>>>> strange stuff with git. Done first draft of shell

    for(int i=0; i<title_len; i++) {
        printf("%s\n", title[i]);
    }
<<<<<<< 23c71b83de8013eb3f120818ea855563bfe29884
    printf("%s", prompt);
=======
    printf("%s", _prompt);
>>>>>>> strange stuff with git. Done first draft of shell
}
