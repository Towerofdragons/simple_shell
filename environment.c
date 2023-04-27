#include "main.h"

int builtin_env(program_data *data)
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

int builtin_set_env(program_data *data)
{
    if (data->tokens[1] == NULL || data->tokens[2] == NULL)
        return (0);
    if (data->tokens[3] != NULL)
    {
        errno = E2BIG;
        perror(data->cmd_name);
        return (5);
    }

    set_env_key(data->tokens[1], data->tokens[2], data);

    return (0);
}

int builtin_unset_env(program_data *data)
{
    if (data->tokens[1] == NULL)
        return (0);
    if (data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(data->cmd_name);
        return (5);
    }
    remove_env_key(data->tokens[1], data);

    return (0);
}
