#include "main.h"
/**
 * read_input - ready terminal and read input
 * @cmd: buffer for cmd input
 *
 * Return: 0 on success, 1 on error
 */



int read_input(char *cmd)
{
	printf("$ ");
	fflush(stdout);
	if (fgets(cmd, MAX_LINE, stdin) == NULL)
	{
		return (1);
	}
	cmd[strcspn(cmd, "\n")] = '\0';
	return (0);
}
