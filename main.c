#include "main.h"

/**
 * main - main entry point for interpreter
 *
 * Return: 0
 */
int main(void)
{
	char cmd[MAX_LINE];
	char *args[MAX_LINE / 2 + 1];
	char *full_path;
        char *cmd_name;
	while (1)
	{
		if (read_input(cmd))
		{
			break;
		}
		if (strcmp(cmd, "exit") == 0)
			break;

	tokenize_input(cmd, args);
	cmd_name = strrchr(args[0], '/');
        if (cmd_name != NULL)
        {
            cmd_name++; 
        }
        else
        {
            cmd_name = args[0];
        }
	full_path = search_path(cmd_name);
		if (full_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		continue;
	}
	execute_command(args, full_path);
	free(full_path);
	}

	return (0);
}
