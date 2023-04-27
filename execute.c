#include "main.h"

int execute_cmd(program_data *d)
{
    int retval = 0, status;
    pid_t pidd;

    retval = builtins_list(d);
    if (retval != -1)
        return (retval);

    retval = search_program(d);
    if (retval)
    {
        return (retval);
    }
    else
    {
        pidd = fork();
        if (pidd == -1)
        {
            perror(d->cmd_name);
            exit(EXIT_FAILURE);
        }
        if (pidd == 0)
        {
            retval = execve(d->tokens[0], d->tokens, d->env_vars);
            if (retval == -1)
                perror(d->cmd_name), exit(EXIT_FAILURE);
        }
        else
        {
            wait(&status);
            if (WIFEXITED(status))
                errno = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                errno = 128 + WTERMSIG(status);
        }
    }
    return (0);
}
