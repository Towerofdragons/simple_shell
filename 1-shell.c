#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_CMD_LEN 1024
#define MAX_ARG_LEN 64

int main(void)
{
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARG_LEN];
    int i;
    pid_t pid;
    int status;

    while (1)
    {
        printf("$ ");
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
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
    return (0);
}
