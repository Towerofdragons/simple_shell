#include "main.h"




void execute_command(char **args, char *full_path) {
    if (fork() == 0) {
        execv(full_path, args);
        perror("execv");
        exit(1);
    } else {
        wait(NULL);
    }
}
