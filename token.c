#include "main.h"
/**
 * _strtok - separates strings with delimiters
 * @line: It´s pointer to array we receive in getline.
 * @delim: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int i;
	char *copy;
	static char *s;
	

	if (line != NULL)
		s = line;
	for (; *s != '\0'; s++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*s == delim[i])
			break;
		}
		if (delim[i] == '\0')
			break;
	}
	copy = s;
	if (*copy == '\0')
		return (NULL);
	for (; *s != '\0'; s++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*s == delim[i])
			{
				*s = '\0';
				s++;
				return (copy);
			}
		}
	}
	return (copy);
}
