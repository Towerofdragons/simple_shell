#include "main.h"



int str_len(char *str)
{
    int length = 0;

    if (str == NULL)
        return (0);

    while (str[length++] != '\0')
    {
    }
    return (--length);
}

char *str_dup(char *str)
{
    char *result;
    int len;
    int i;

    if (str == NULL)
        return (NULL);

    len = str_len(str) + 1;

    result = malloc(sizeof(char) * len);

    if (result == NULL)
    {
        errno = ENOMEM;
        perror("Error");
        return (NULL);
    }
    for (i = 0; i < len; i++)
    {
        result[i] = str[i];
    }

    return (result);
}

int str_cmp(char *string1, char *string2, int number)
{
    int iterator;

    if (string1 == NULL && string2 == NULL)
        return (1);

    if (string1 == NULL || string2 == NULL)
        return (0);

    if (number == 0) /* infinite longitud */
    {
        if (str_len(string1) != str_len(string2))
            return (0);
        for (iterator = 0; string1[iterator]; iterator++)
        {
            if (string1[iterator] != string2[iterator])
                return (0);
        }
        return (1);
    }
    else /* if there is a number of chars to be compared */
    {
        for (iterator = 0; iterator < number ; iterator++)
        {
            if (string1[iterator] != string2[iterator])
                return (0);
        }
        return (1);
    }
}


char *str_cat(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = str_len(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = str_len(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (length1 = 0; string1[length1] != '\0'; length1++)
		result[length1] = string1[length1];
	free(string1);

	/* copy of string2 */
	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		result[length1] = string2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}


/**
 * str_reverse - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void reverse_str(char *string)
{
    int i = 0, length = str_len(string) - 1;
    char hold;

    while (i < length)
    {
        hold = string[i];
        string[i++] = string[length];
        string[length--] = hold;
    }
}
