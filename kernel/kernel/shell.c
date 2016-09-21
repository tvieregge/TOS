#include <kernel/shell.h>
#include <kernel/tty.h>

char const * const title[] = {
"  __________  _____",
" /_  __/ __ \\/ ___/",
"  / / / / / /\\__ \\ ",
" / / / /_/ /___/ / ",
"/_/  \\____//____/"
}; 

char* commands[] = {
    "help",
    "time"
};

void process_cmd() {

}

void shell_send_char(const char c) {
    static char current_input[32];
    static unsigned int cur_input_index = 0;

    if(c == '\n') {
        current_input[cur_input_index] = '\0';
        process_cmd();
    }
    current_input[cur_input_index] = c;
    cur_input_index += 1;
    putchar(c);
}

void init_shell(const char* prompt) {
    int title_len = sizeof(title)/sizeof(title[0]);

    for(int i=0; i<title_len; i++) {
        printf("%s\n", title[i]);
    }
    printf("%s", prompt);
}
