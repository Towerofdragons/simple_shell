#include "main.h"

int check_file(char *full_path);

int search_program(program_data *d)
{
    int i = 0, ret_code = 0;
    char **dirs;

    if (!d->cmd_name)
        return (2);

    if (d->cmd_name[0] == '/' || d->cmd_name[0] == '.')
        return (check_file(d->cmd_name));

    free(d->tokens[0]);
    d->tokens[0] = str_cat(str_dup("/"), d->cmd_name);
    if (!d->tokens[0])
        return (2);

    dirs = tokenize_path(d);

    if (!dirs || !dirs[0])
    {
        errno = 127;
        return (127);
    }
    for (i = 0; dirs[i]; i++)
    {
        dirs[i] = str_cat(dirs[i], d->tokens[0]);
        ret_code = check_file(dirs[i]);
        if (ret_code == 0 || ret_code == 126)
        {
            errno = 0;
            free(d->tokens[0]);
            d->tokens[0] = str_dup(dirs[i]);
            free_pointer_array(dirs);
            return (ret_code);
        }
    }
    free(d->tokens[0]);
    d->tokens[0] = NULL;
    free_pointer_array(dirs);
    return (ret_code);
}

char **tokenize_path(program_data *d)
{
    int i;
    int counter;
    char **tokens = NULL;
    char *PATH;

    i = 0;
    counter = 2;
    PATH = get_env_key("PATH", d);

    if ((PATH == NULL) || PATH[0] == '\0')
        return (NULL);

    PATH = str_dup(PATH);

    for (i = 0; PATH[i]; i++)
    {
        if (PATH[i] == ':')
            counter++;
    }

    tokens = malloc(sizeof(char *) * counter);

    i = 0;
    tokens[i] = str_dup(_strtok(PATH, ":"));
    while (tokens[i++])
    {
        tokens[i] = str_dup(_strtok(NULL, ":"));
    }

    free(PATH);
    PATH = NULL;
    return (tokens);
}

int check_file(char *full_path)
{
    struct stat sb;

    if (stat(full_path, &sb) != -1)
    {
        if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
        {
            errno = 126;
            return (126);
        }
        return (0);
    }
    errno = 127;
    return (127);
}
