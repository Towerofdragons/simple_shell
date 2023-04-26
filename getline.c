#include "main.h"


int _getline(data_of_program *d)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exists */
		for (i = 0; commands[i]; i++)
		{
			free(commands[i]);
			commands[i] = NULL;
		}

		/* read from the file descriptor int to buff */
		bytes_read = read(d->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines for \n or ; */
		i = 0;
		do {
			commands[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
			/*checks and split for && and || operators*/
			i = check_logic_ops(commands, i, array_operators);
		} while (commands[i++]);
	}


	d->input_line = commands[0];
	for (i = 0; commands[i]; i++)
	{
		commands[i] = commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (str_length(d->input_line));
}


int check_logic_ops(char *commandslst[], int i, char operators[])
{
	char *temp = NULL;
	int j;

	/* checks for the & char in the command line*/
	for (j = 0; commandslst[i] != NULL  && commandslst[i][j]; j++)
	{
		if (commandslst[i][j] == '&' && commandslst[i][j + 1] == '&')
		{
			/* split the line when chars && was found */
			temp = commandslst[i];
			commandslst[i][j] = '\0';
			commandslst[i] = str_duplicate(commandslst[i]);
			commandslst[i + 1] = str_duplicate(temp + j + 2);
			i++;
			operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (commandslst[i][j] == '|' && commandslst[i][j + 1] == '|')
		{
			/* split the line when chars || was found */
			temp = commandslst[i];
			commandslst[i][j] = '\0';
			commandslst[i] = str_duplicate(commandslst[i]);
			commandslst[i + 1] = str_duplicate(temp + j + 2);
			i++;
			operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
