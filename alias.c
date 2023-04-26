#include "main.h"


int print_alias(data_of_program *data, char *alias)
{
	int i;
	int j;
	int length;
	char buff[250] = {'\0'};

	if (data->alias_list)
	{
		length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, length)
				&&	data->alias_list[i][length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buff[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buff[j + 1] = '\0';
				buffer_add(buff, "'");
				buffer_add(buff, data->alias_list[i] + j + 1);
				buffer_add(buff, "'\n");
				_print(buff);
			}
		}
	}

	return (0);
}


char *get_alias(data_of_program *data, char *name)
{
	int i, length;

	
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (str_compare(name, data->alias_list[i], length) &&
			data->alias_list[i][length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[i] + length + 1);
		}
	}
	
	return (NULL);

}


int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buff[250] = {'0'}, *temp = NULL;

	
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buff[i] = alias_string[i];
		else
		{
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buff, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}

	
	if (temp)
	{
		buffer_add(buff, "=");
		buffer_add(buff, temp);
		data->alias_list[j] = str_duplicate(buff);
	}
	else 
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
