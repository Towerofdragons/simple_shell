#include "main.h"

int check_file(char *full_path);


int find_program(data_of_program *d)
{
	int i = 0, ret_code = 0;
	char **dirs;

	if (!d->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (d->command_name[0] == '/' || d->command_name[0] == '.')
		return (check_file(d->command_name));

	free(d->tokens[0]);
	d->tokens[0] = str_concat(str_duplicate("/"), d->command_name);
	if (!d->tokens[0])
		return (2);

	dirs = tokenize_path(d);/* search in the PATH */

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dirs[i]; i++)
	{/* appends the function_name to path */
		dirs[i] = str_concat(dirs[i], d->tokens[0]);
		ret_code = check_file(dirs[i]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(d->tokens[0]);
			d->tokens[0] = str_duplicate(dirs[i]);
			free_array_of_pointers(dirs);
			return (ret_code);
		}
	}
	free(d->tokens[0]);
	d->tokens[0] = NULL;
	free_array_of_pointers(dirs);
	return (ret_code);
}


char **tokenize_path(data_of_program *d)
{
	int i;
	int counter;
	char **tokens = NULL;
	char *PATH;

	i = 0;
	counter = 2;
	PATH = env_get_key("PATH", d);

	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* find the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter);

	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}


int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
