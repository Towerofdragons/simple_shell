#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_LINE 80

extern char **environ;
char *search_path(char *cmd);
int read_input(char *cmd);
void tokenize_input(char *cmd, char **args);
void execute_command(char **args, char *full_path);


#endif
