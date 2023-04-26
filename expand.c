#include "main.h"

void expand_variables(data_of_program *d)
{
	int i;
	int j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (d->input_line == NULL)
		return;
	buffer_add(line, d->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, d->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, d->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = env_get_key(expansion, d);
			line[i] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(d->input_line, line, 0))
	{
		free(d->input_line);
		d->input_line = str_duplicate(line);
	}
}


void expand_alias(data_of_program *d)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (d->input_line == NULL)
		return;

	buffer_add(line, d->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias(d, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			line[i] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(d->input_line);
		d->input_line = str_duplicate(line);
	}
}


int buffer_add(char *buff, char *str_to_add)
{
	int length;
	int i;

	length = str_length(buff);
	for (i = 0; str_to_add[i]; i++)
	{
		buff[length + i] = str_to_add[i];
	}
	buff[length + i] = '\0';
	return (length + i);
}
