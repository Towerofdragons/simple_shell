#include "main.h"



int main(int argc, char *argv[]) {
    char cmd[MAX_LINE];
    char *args[MAX_LINE/2 + 1];
    char *full_path;
   setenv("PATH", "/path/to/directory", 1);
    
    if (argc > 1) {
        freopen(argv[1], "r", stdin);
    }
    
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
    freopen("/dev/tty", "r", stdin);    
    return 0;
}
