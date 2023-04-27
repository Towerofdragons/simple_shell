#include "main.h"


int get_input_line(program_data *d)
{
    char buff[BUFFER_SIZE] = {'\0'};
    static char *commands[10] = {NULL};
    static char array_operators[10] = {'\0'};
    ssize_t bytes_read, i = 0;

    if (!commands[0] || (array_operators[0] == '&' && errno != 0) ||
        (array_operators[0] == '|' && errno == 0))
    {
        for (i = 0; commands[i]; i++)
        {
            free(commands[i]);
            commands[i] = NULL;
        }

        bytes_read = read(d->file_desc, &buff, BUFFER_SIZE - 1);
        if (bytes_read == 0)
            return (-1);

        i = 0;
        do {
            commands[i] = str_dup(_strtok(i ? NULL : buff, "\n;"));
            i = check_logical_ops(commands, i, array_operators);
        } while (commands[i++]);
    }

    d->input_str = commands[0];
    for (i = 0; commands[i]; i++)
    {
        commands[i] = commands[i + 1];
        array_operators[i] = array_operators[i + 1];
    }

    return (str_len(d->input_str));
}

int check_logical_ops(char *cmd_array[], int i, char op_array[])
{
    char *temp = NULL;
    int j;

    for (j = 0; cmd_array[i] != NULL && cmd_array[i][j]; j++)
    {
        if (cmd_array[i][j] == '&' && cmd_array[i][j + 1] == '&')
        {
            temp = cmd_array[i];
            cmd_array[i][j] = '\0';
            cmd_array[i] = str_dup(cmd_array[i]);
            cmd_array[i + 1] = str_dup(temp + j + 2);
            i++;
            op_array[i] = '&';
            free(temp);
            j = 0;
        }
        if (cmd_array[i][j] == '|' && cmd_array[i][j + 1] == '|')
        {
            temp = cmd_array[i];
            cmd_array[i][j] = '\0';
            cmd_array[i] = str_dup(cmd_array[i]);
            cmd_array[i + 1] = str_dup(temp + j + 2);
            i++;
            op_array[i] = '|';
            free(temp);
            j = 0;
        }
    }
    return (i);
}
