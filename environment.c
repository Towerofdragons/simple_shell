#include "main.h"

int builtin_env(data_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokens[1] + i + 1, data);

				
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}


int builtin_set_env(data_of_program *d)
{
	
	if (d->tokens[1] == NULL || d->tokens[2] == NULL)
		return (0);
	if (d->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(d->command_name);
		return (5);
	}

	env_set_key(d->tokens[1], d->tokens[2], d);

	return (0);
}


int builtin_unset_env(data_of_program *d)
{
	
	if (d->tokens[1] == NULL)
		return (0);
	if (d->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(d->command_name);
		return (5);
	}
	env_remove_key(d->tokens[1], d);

	return (0);
}
