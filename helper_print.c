#include "main.h"

int _print(char *stringval)
{
    return (write(STDOUT_FILENO, stringval, str_length(stringval)));
}

int _printe(char *stringval)
{
    return (write(STDERR_FILENO, stringval, str_length(stringval)));
}

int _print_error(int errorcode, program_data *data)
{
    char n_as_string[10] = {'\0'};

    long_to_string((long) data->cmd_count, n_as_string, 10);

    if (errorcode == 2 || errorcode == 3)
    {
        _printe(data->prog_name);
        _printe(": ");
        _printe(n_as_string);
        _printe(": ");
        _printe(data->tokens[0]);
        if (errorcode == 2)
            _printe(": Illegal number: ");
        else
            _printe(": can't cd to ");
        _printe(data->tokens[1]);
        _printe("\n");
    }
    else if (errorcode == 127)
    {
        _printe(data->prog_name);
        _printe(": ");
        _printe(n_as_string);
        _printe(": ");
        _printe(data->cmd_name);
        _printe(": not found\n");
    }
    else if (errorcode == 126)
    {
        _printe(data->prog_name);
        _printe(": ");
        _printe(n_as_string);
        _printe(": ");
        _printe(data->cmd_name);
        _printe(": Permission denied\n");
    }
    return (0);
}
