#include "main.h"

void expand_variables(program_data *data)
{
    int i;
    int j;
    char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->input_str == NULL)
        return;
    buffer_add(line, data->input_str);
    for (i = 0; line[i]; i++)
        if (line[i] == '#')
            line[i--] = '\0';
        else if (line[i] == '$' && line[i + 1] == '?')
        {
            line[i] = '\0';
            long_to_string(errno, expansion, 10);
            buffer_add(line, expansion);
            buffer_add(line, data->input_str + i + 2);
        }
        else if (line[i] == '$' && line[i + 1] == '$')
        {
            line[i] = '\0';
            long_to_string(getpid(), expansion, 10);
            buffer_add(line, expansion);
            buffer_add(line, data->input_str + i + 2);
        }
        else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
            continue;
        else if (line[i] == '$')
        {
            for (j = 1; line[i + j] && line[i + j] != ' '; j++)
                expansion[j - 1] = line[i + j];
            temp = get_env_key(expansion, data);
            line[i] = '\0', expansion[0] = '\0';
            buffer_add(expansion, line + i + j);
            temp ? buffer_add(line, temp) : 1;
            buffer_add(line, expansion);
        }
    if (!str_compare(data->input_str, line, 0))
    {
        free(data->input_str);
        data->input_str = str_duplicate(line);
    }
}

void expand_alias(program_data *data)
{
    int i, j, was_expanded = 0;
    char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->input_str == NULL)
        return;

    buffer_add(line, data->input_str);

    for (i = 0; line[i]; i++)
    {
        for (j = 0; line[i + j] && line[i + j] != ' '; j++)
            expansion[j] = line[i + j];
        expansion[j] = '\0';

        temp = get_alias_value(data, expansion);
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
        free(data->input_str);
        data->input_str = str_duplicate(line);
    }
}

int buffer_add(char *buff, char *str_to_add)
{
    int length;
    int i;

	length = str_length(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
