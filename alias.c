#include "main.h"

int print_alias_value(program_data *data, char *alias)
{
    int i;
    int j;
    int length;
    char buff[250] = {'\0'};

    if (data->alias_arr)
    {
        length = str_len(alias);
        for (i = 0; data->alias_arr[i]; i++)
        {
            if (!alias || (str_cmp(data->alias_arr[i], alias, length)
                && data->alias_arr[i][length] == '='))
            {
                for (j = 0; data->alias_arr[i][j]; j++)
                {
                    buff[j] = data->alias_arr[i][j];
                    if (data->alias_arr[i][j] == '=')
                        break;
                }
                buff[j + 1] = '\0';
                add_to_buffer(buff, "'");
                add_to_buffer(buff, data->alias_arr[i] + j + 1);
                add_to_buffer(buff, "'\n");
                print_str(buff);
            }
        }
    }

    return (0);
}

char *get_alias_value(program_data *data, char *name)
{
    int i, length;

    if (name == NULL || data->alias_arr == NULL)
        return (NULL);

    length = str_len(name);

    for (i = 0; data->alias_arr[i]; i++)
    {
        if (str_cmp(name, data->alias_arr[i], length) &&
            data->alias_arr[i][length] == '=')
        {
            return (data->alias_arr[i] + length + 1);
        }
    }

    return (NULL);
}

int set_alias_value(char *alias_str, program_data *data)
{
    int i, j;
    char buff[250] = {'0'}, *temp = NULL;

    if (alias_str == NULL || data->alias_arr == NULL)
        return (1);

    for (i = 0; alias_str[i]; i++)
        if (alias_str[i] != '=')
            buff[i] = alias_str[i];
        else
        {
            temp = get_alias_value(data, alias_str + i + 1);
            break;
        }

    for (j = 0; data->alias_arr[j]; j++)
        if (str_cmp(buff, data->alias_arr[j], i) &&
            data->alias_arr[j][i] == '=')
        {
            free(data->alias_arr[j]);
            break;
        }

    if (temp)
    {
        add_to_buffer(buff, "=");
        add_to_buffer(buff, temp);
        data->alias_arr[j] = str_dup(buff);
    }
    else
        data->alias_arr[j] = str_dup(alias_str);
    return (0);
}
