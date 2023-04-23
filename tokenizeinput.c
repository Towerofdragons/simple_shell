#include "main.h"

/**
 * tokenize_input - parse input on interpreter
 * @cmd: original command from terminal
 * @args: array of strings for individual command tokens
 *
 * Return: nothing
 */
void tokenize_input(char *cmd, char **args)
{
	char *token;
	int i = 0;

	token = strtok(cmd, " ");
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
}
