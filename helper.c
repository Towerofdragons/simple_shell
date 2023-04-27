#include "main.h"

void free_recur_data(program_data *d)
{
    if (d->tokens)
        free_pointer_array(d->tokens);
    if (d->input_str)
        free(d->input_str);
    if (d->cmd_name)
        free(d->cmd_name);

    d->input_str = NULL;
    d->cmd_name = NULL;
    d->tokens = NULL;
}

void free_all(program_data *d)
{
    if (d->file_desc != 0)
    {
        if (close(d->file_desc))
            perror(d->prog_name);
    }
    free_recurrent_data(d);
    free_pointer_array(d->env_vars);
    free_pointer_array(d->alias_arr);
}

void free_pointer_array(char **arr)
{
    int i;

    if (arr != NULL)
    {
        for (i = 0; arr[i]; i++)
            free(arr[i]);

        free(arr);
        arr = NULL;
    }
}
