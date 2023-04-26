#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARG_LEN 64

int main(void)
{
    char *cmd = NULL;
    size_t cmd_len = 0;
    char *args[MAX_ARG_LEN];
    int i;
    pid_t pid;
    int status;

    while (1)
    {
        printf("$ ");
        if (getline(&cmd, &cmd_len, stdin) == -1)
        {
            printf("\n");
            exit(0);
        }
        cmd[strlen(cmd) - 1] = '\0';
        args[0] = strtok(cmd, " ");
        i = 0;
        while (args[i] != NULL)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }
        if (args[0] == NULL)
            continue;
        pid = fork();
        if (pid == 0)
        {
            if (execve(args[0], args, NULL) == -1)
                perror("Error");
            exit(0);
        }
        else
            wait(&status);
    }
    free(cmd);
    return (0);
}
