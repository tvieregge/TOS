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
