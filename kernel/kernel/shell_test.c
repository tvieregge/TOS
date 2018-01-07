#include <kernel/shell.h>
#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "shell_internal.h"

void shell_test(void) {
    printf("TEST RUNNING\n");
    
    char *line = "";
    char *s1 = "a";
    char *s2 = "ab";
    line = shell_add_char(line, 'a');
    assert(memcmp(line, s1, strlen(s1)) == 0);
    line = shell_add_char(line, 'b');
    assert(memcmp(line, s2, strlen(s2)) == 0);
    //line = shell_add_char(line, '\b');
    //assert(memcmp(line, "a") == 0);
}
