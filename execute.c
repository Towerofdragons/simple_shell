#include "main.h"
/**
 * execute_command - execute specific command
 * @args:arguements for execution
 * @full_path: path to program file
 *
 * Return: Nothing
 */

void execute_command(char **args, char *full_path)
{
	if (fork() == 0)
	{
	execv(full_path, args);
	perror("execv");
	exit(1);
	}
	else
	{
		wait(NULL);
	}
}
