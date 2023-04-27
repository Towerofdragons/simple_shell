#include "main.h"

/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_vars(program_data *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_str == NULL)
		return;
	add_to_buffer(line, data->input_str);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			convert_long_to_str(errno, expansion, 10);
			add_to_buffer(line, expansion);
			add_to_buffer(line, data->input_str + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			convert_long_to_str(getpid(), expansion, 10);
			add_to_buffer(line, expansion);
			add_to_buffer(line, data->input_str + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = get_env_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			add_to_buffer(expansion, line + i + j);
			temp ? add_to_buffer(line, temp) : 1;
			add_to_buffer(line, expansion);
		}
	if (!str_cmp(data->input_str, line, 0))
	{
		free(data->input_str);
		data->input_str = str_dup(line);
	}
}

/**
 * expand_aliases - expand aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_aliases(program_data *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_str == NULL)
		return;

	add_to_buffer(line, data->input_str);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias_value(data, expansion);

	if (temp)
	{
		expansion[0] = '\0';
		add_to_buffer(expansion, line + i + j);
		line[i] = '\0';
		add_to_buffer(line, temp);
		line[str_len(line)] = '\0';
		add_to_buffer(line, expansion);
		was_expanded = 1;
	}
	break;
}
if (was_expanded)
{
	free(data->input_str);
	data->input_str = str_dup(line);
}
}

/**
 * add_to_buffer - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int add_to_buffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = str_len(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
