#include "main.h"

void convert_long_to_str(long number, char *string, int base)
{
    int index = 0, is_negative = 0;
    long quotient = number;
    char letters[] = {"0123456789abcdef"};

    if (quotient == 0)
        string[index++] = '0';

    if (string[0] == '-')
        is_negative = 1;

    while (quotient)
    {
        if (quotient < 0)
            string[index++] = letters[-(quotient % base)];
        else
            string[index++] = letters[quotient % base];
        quotient /= base;
    }
    if (is_negative)
        string[index++] = '-';

    string[index] = '\0';
    reverse_str(string);
}

int str_to_int(char *s)
{
    int sign = 1;
    unsigned int number = 0;

    while (!('0' <= *s && *s <= '9') && *s != '\0')
    {
        if (*s == '-')
            sign *= -1;
        if (*s == '+')
            sign *= +1;
        s++;
    }

    while ('0' <= *s && *s <= '9' && *s != '\0')
    {
        number = (number * 10) + (*s - '0');
        s++;
    }
    return (number * sign);
}

int count_chars(char *string, char *character)
{
    int i = 0, counter = 0;

    for (; string[i]; i++)
    {
        if (string[i] == character[0])
            counter++;
    }
    return (counter);
}
