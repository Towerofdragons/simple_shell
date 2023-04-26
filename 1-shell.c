#include "main.h"

#define MAX_ARG_LEN 64

/**
 * main - simple UNIX command line interpreter
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
char *cmd = NULL;
size_t cmd_len = 0;
char *args[MAX_ARG_LEN];
int i;
pid_t pid;
int status;

(void)argc;
while (1)
{
write(STDOUT_FILENO, "$ ", 2);
if (getline(&cmd, &cmd_len, stdin) == -1)
{
write(STDOUT_FILENO, "\n", 1);
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
{
write(STDERR_FILENO, argv[0], strlen(argv[0]));
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, "1", 1);
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, args[0], strlen(args[0]));
write(STDERR_FILENO, ": not found\n", 12);
exit(127);
}
}
else
wait(&status);
}
free(cmd);
return (0);
}
