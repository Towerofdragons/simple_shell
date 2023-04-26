#include "main.h"
void execute_pipe(char **args1, char **args2)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Child reads from pipe */
        close(pipefd[1]);          /* Close unused write end */
        dup2(pipefd[0], STDIN_FILENO);   /* Redirect stdin */
        close(pipefd[0]);          /* Close used read end */
        execvp(args2[0], args2);
        perror(args2[0]);
        exit(EXIT_FAILURE);
    } else {
        /* Parent writes argv[1] to pipe */
        close(pipefd[0]);          /* Close unused read end */
        dup2(pipefd[1], STDOUT_FILENO);  /* Redirect stdout */
        close(pipefd[1]);          /* Close used write end */
        execvp(args1[0], args1);
        perror(args1[0]);
        exit(EXIT_FAILURE);
    }
}
