#include "main.h"



void tokenize_input(char *cmd, char **args) {
    char *token;
    int i = 0;
    token = strtok(cmd, " ");
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
}
