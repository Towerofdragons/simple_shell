#include "main.h"



/**
 * builtins_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/


int builtins_list(program_data *data)
{
	int i;
	builtin_cmds x[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};
	for (i = 0; x[i].cmd_name != NULL; i++)
	{
		if (str_cmp(x[i].cmd_name, data->cmd_name, 0))
		{
			return (x[i].func(data));
		}

	}
	return (-1);
}
