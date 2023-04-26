#include "main.h"

void free_recurrent_data(data_of_program *d)
{
	if (d->tokens)
		free_array_of_pointers(d->tokens);
	if (d->input_line)
		free(d->input_line);
	if (d->command_name)
		free(d->command_name);

	d->input_line = NULL;
	d->command_name = NULL;
	d->tokens = NULL;
}


void free_all_data(data_of_program *d)
{
	if (d->file_descriptor != 0)
	{
		if (close(d->file_descriptor))
			perror(d->program_name);
	}
	free_recurrent_data(d);
	free_array_of_pointers(d->env);
	free_array_of_pointers(d->alias_list);
}


void free_array_of_pointers(char **arr)
{
	int i;

	if (arr != NULL)
	{
		for (i = 0; arr[i]; i++)
			free(arr[i]);

		free(arr);
		arr = NULL;
	}
}
