#include "main.h"

/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on success.
 */
int main(int argc, char *argv[], char *env[])
{
    program_data data_struct = {NULL}, *data = &data_struct;
    char *prompt = "";

    init_data(data, argc, argv, env);

    signal(SIGINT, handle_sigint);

    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
    {
        errno = 2;
        prompt = PROMPT_MSG;
    }
    errno = 0;
    run_sisifo(prompt, data);
    return (0);
}

/**
 * handle_sigint - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is sent to the program
 * @sig: option of the prototype
 */
void handle_sigint(int sig UNUSED)
{
    print_str("\n");
    print_str(PROMPT_MSG);
}

/**
 * init_data - initialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments passed to the program execution
 * @env: environ passed to the program execution
 * @argc: number of values received from the command line
 */
void init_data(program_data *data, int argc, char *argv[], char **env)
{
    int i = 0;

    data->prog_name = argv[0];
    data->input_str = NULL;
    data->cmd_name = NULL;
    data->cmd_count = 0;

    if (argc == 1)
        data->file_desc = STDIN_FILENO;
    else
    {
        data->file_desc = open(argv[1], O_RDONLY);
        if (data->file_desc == -1)
        {
            print_err_str(data->prog_name);
            print_err_str(": 0: Can't open ");
            print_err_str(argv[1]);
            print_err_str("\n");
            exit(127);
        }
    }
    data->tokens = NULL;
    data->env_vars = malloc(sizeof(char *) * 50);
    if (env)
    {
        for (; env[i]; i++)
        {
            data->env_vars[i] = str_dup(env[i]);
        }
    }

data->env_vars[i] = NULL;
env = data->env_vars;

data->alias_arr = malloc(sizeof(char *) * 20);
for (i = 0; i < 20; i++)
{
    data->alias_arr[i] = NULL;
}
}

/**
 * run_sisifo - its an infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its an infinite loop that shows the prompt
 */
void run_sisifo(char *prompt, program_data *data)
{
    int err_code = 0, str_len = 0;

    while (++(data->cmd_count))
    {
        print_str(prompt);
        err_code = str_len = get_input_line(data);

        if (err_code == EOF)
        {
            free_all(data);
            exit(errno);
        }
        if (str_len >= 1)
        {
            expand_aliases(data);
            expand_vars(data);
            tokenize_input(data);
            if (data->tokens[0])
            {
                err_code = execute_cmd(data);
                if (err_code != 0)
                    print_error_msg(err_code, data);
            }
            free_recur_data(data);
        }
    }
}
