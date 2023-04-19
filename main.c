#include "main.h"









int main(void) {
    char cmd[MAX_LINE];
    char *args[MAX_LINE/2 + 1];
    char *full_path;
    
    while (1) {
       if (read_input(cmd)) {
        break;
        }
        if (strcmp(cmd, "exit") == 0) {
            break;
        }
        tokenize_input(cmd, args);
        full_path = search_path(args[0]);
        if (full_path == NULL) {
            fprintf(stderr, "%s: command not found\n", args[0]);
            continue;
        }
        execute_command(args, full_path);
        free(full_path);
    }
    
    return 0;
}
