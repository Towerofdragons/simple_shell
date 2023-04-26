#include "main.h"

int env_cmd(program_data *data)
{
    int i;
    char cpname[50] = {'\0'};
    char *var_copy = NULL;

    if (data->tokens[1] == NULL)
        print_env_vars(data);
    else
    {
        for (i = 0; data->tokens[1][i]; i++)
        {
            if (data->tokens[1][i] == '=')
            {
                var_copy = str_dup(get_env_key(cpname, data));
                if (var_copy != NULL)
                    set_env_key(cpname, data->tokens[1] + i + 1, data);

                print_env_vars(data);
                if (get_env_key(cpname, data) == NULL)
                {
                    print_str(data->tokens[1]);
                    print_str("\n");
                }
                else
                {
                    set_env_key(cpname, var_copy, data);
                    free(var_copy);
                }
                return (0);
            }
            cpname[i] = data->tokens[1][i];
        }
        errno = 2;
        perror(data->cmd_name);
        errno = 127;
    }
    return (0);
}

int set_env_cmd(program_data *d)
{
    if (d->tokens[1] == NULL || d->tokens[2] == NULL)
        return (0);
    if (d->tokens[3] != NULL)
    {
        errno = E2BIG;
        perror(d->cmd_name);
        return (5);
    }

    set_env_key(d->tokens[1], d->tokens[2], d);

    return (0);
}

int unset_env_cmd(program_data *d)
{
    if (d->tokens[1] == NULL)
        return (0);
    if (d->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(d->cmd_name);
        return (5);
    }
    remove_env_key(d->tokens[1], d);

    return (0);
}
