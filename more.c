#include "main.h"

int builtin_exit(program_data *data)
{
    int i;

    if (data->tokens[1] != NULL)
    {
        for (i = 0; data->tokens[1][i]; i++)
            if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
                && data->tokens[1][i] != '+')
            {
                errno = 2;
                return (2);
            }
        errno = str_to_int(data->tokens[1]);
    }
    free_all(data);
    exit(errno);
}

int builtin_cd(program_data *data)
{
    char *dir_home = get_env_key("HOME", data), *dir_old = NULL;
    char old_dir[128] = {0};
    int error_code = 0;

    if (data->tokens[1])
    {
        if (str_cmp(data->tokens[1], "-", 0))
        {
            dir_old = get_env_key("OLDPWD", data);
            if (dir_old)
                error_code = set_working_dir(data, dir_old);
            print_str(get_env_key("PWD", data));
            print_str("\n");

            return (error_code);
        }
        else
        {
            return (set_working_dir(data, data->tokens[1]));
        }
    }
    else
    {
        if (!dir_home)
            dir_home = getcwd(old_dir, 128);

        return (set_working_dir(data, dir_home));
    }
    return (0);
}

int set_work_directory(program_data *data, char *new_dir)
{
    char old_dir[128] = {0};
    int err_code = 0;

    getcwd(old_dir, 128);

    if (!str_cmp(old_dir, new_dir, 0))
    {
        err_code = chdir(new_dir);
        if (err_code == -1)
        {
            errno = 2;
            return (3);
        }
        set_env_key("PWD", new_dir, data);
    }
    set_env_key("OLDPWD", old_dir, data);
    return (0);
}

int builtin_help(program_data *data)
{
    int i, length = 0;
    char *messages[6] = {NULL};

    messages[0] = HELP_MSG;

    if (data->tokens[1] == NULL)
    {
        print_str(messages[0] + 6);
        return (1);
    }
    if (data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(data->cmd_name);
        return (5);
    }
    messages[1] = HELP_EXIT_MSG;
    messages[2] = HELP_ENV_MSG;
    messages[3] = HELP_SETENV_MSG;
    messages[4] = HELP_UNSETENV_MSG;
    messages[5] = HELP_CD_MSG;

    for (i = 0; messages[i]; i++)
    {
        length = str_len(data->tokens[1]);
        if (str_cmp(data->tokens[1], messages[i], length))
        {
            print_str(messages[i] + length + 1);
            return (1);
        }
    }
    errno = EINVAL;
    perror(data->cmd_name);
    return (0);
}

int builtin_alias(program_data *data);
{
    int i = 0;

    if (data->tokens[1] == NULL)
        return (print_alias_value(data, NULL));

    while (data->tokens[++i])
    {
        if (count_chars(data->tokens[i], "="))
            set_alias_value(data->tokens[i], data);
        else
            print_alias_value(data, data->tokens[i]);
    }

    return (0);
}
	
