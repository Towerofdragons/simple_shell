#include "shell.h"

char *get_env_key(char *key, program_data *data)
{
    int i, key_len = 0;

    if (key == NULL || data->env_vars == NULL)
        return (NULL);

    key_len = str_len(key);

    for (i = 0; data->env_vars[i]; i++)
    {
        if (str_cmp(key, data->env_vars[i], key_len) && data->env_vars[i][key_len] == '=')
        {
            return (data->env_vars[i] + key_len + 1);
        }
    }
    return (NULL);
}

int set_env_key(char *key, char *value, program_data *data)
{
    int i, key_len = 0, is_new_key = 1;

    if (key == NULL || value == NULL || data->env_vars == NULL)
        return (1);

    key_len = str_len(key);

    for (i = 0; data->env_vars[i]; i++)
    {
        if (str_cmp(key, data->env_vars[i], key_len) && data->env_vars[i][key_len] == '=')
        {
            is_new_key = 0;
            free(data->env_vars[i]);
            break;
        }
    }

    data->env_vars[i] = str_cat(str_dup(key), "=");
    data->env_vars[i] = str_cat(data->env_vars[i], value);

if (is_new_key)
{
    data->env_vars[i + 1] = NULL;
}
return (0);
}

int remove_env_key(char *key, program_data *data)
{
    int i, key_len = 0;

    if (key == NULL || data->env_vars == NULL)
        return (0);

    key_len = str_len(key);

    for (i = 0; data->env_vars[i]; i++)
    {
        if (str_cmp(key, data->env_vars[i], key_len) && data->env_vars[i][key_len] == '=')
        {
            free(data->env_vars[i]);

            i++;
            for (; data->env_vars[i]; i++)
            {
                data->env_vars[i - 1] = data->env_vars[i];
            }
            data->env_vars[i - 1] = NULL;
            return (1);
        }
    }
    return (0);
}

void print_env_vars(program_data *data)
{
    int j;

    for (j = 0; data->env_vars[j]; j++)
    {
        print_str(data->env_vars[j]);
        print_str("\n");
    }
}
