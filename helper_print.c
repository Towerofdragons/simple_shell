#include "main.h"

int printstr(char *str)
{
    return (write(STDOUT_FILENO, str, str_len(str)));
}

int print_err_str(char *str)
{
    return (write(STDERR_FILENO, str, str_len(str)));
}

int print_error_msg(int err_code, program_data *data)
{
    char n_as_string[10] = {'\0'};

    convert_long_to_str((long) data->cmd_count, n_as_string, 10);

    if (err_code == 2 || err_code == 3)
    {
         print_err_str(data->prog_name);
        print_err_str(": ");
        print_err_str(n_as_string);
        print_err_str(": ");
        print_err_str(data->tokens[0]);
        if (err_code == 2)
            print_err_str(": Illegal number: ");
        else
            print_err_str(": can't cd to ");
        print_err_str(data->tokens[1]);
        print_err_str("\n");
    }
    else if (err_code == 127)
    {
        print_err_str(data->prog_name);
        print_err_str(": ");
        print_err_str(n_as_string);
        print_err_str(": ");
        print_err_str(data->cmd_name);
        print_err_str(": not found\n");
    }
    else if (err_code == 126)
    {
        print_err_str(data->prog_name);
        print_err_str(": ");
        print_err_str(n_as_string);
        print_err_str(": ");
        print_err_str(data->cmd_name);
        print_err_str(": Permission denied\n");
    }
    return (0);
}
