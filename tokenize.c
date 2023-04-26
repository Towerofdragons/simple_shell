#include "main.h"

void tokenize_input(program_data *data)
{
    char *delimiter = " \t";
    int i, j, counter = 2, length;

    length = str_len(data->input_str);
    if (length)
    {
        if (data->input_str[length - 1] == '\n')
            data->input_str[length - 1] = '\0';
    }

    for (i = 0; data->input_str[i]; i++)
    {
        for (j = 0; delimiter[j]; j++)
        {
            if (data->input_str[i] == delimiter[j])
                counter++;
        }
    }

    data->tokens = malloc(counter * sizeof(char *));
    if (data->tokens == NULL)
    {
        perror(data->prog_name);
        exit(errno);
    }
    i = 0;
    data->tokens[i] = str_dup(_strtok(data->input_str, delimiter));
    data->cmd_name = str_dup(data->tokens[0]);
    while (data->tokens[i++])
    {
        data->tokens[i] = str_dup(_strtok(NULL, delimiter));
    }
}
