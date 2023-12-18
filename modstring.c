// modstring.c

#include "newheader.h"

/**
 * compareDirectoryStrings - compares strings to find a directory.
 *
 * @s1: string.
 * @s2: string.
 *
 * Return: 0 if match, any other number otherwise.
 **/
int compareDirectoryStrings(char *s1, char *s2)
{
    int i = 0;

    for (; (*s2 != '\0' && *s1 != '\0') && *s1 == *s2; s1++)
    {
        if (i == 3)
            break;
        i++;
        s2++;
    }

    return (*s1 - *s2);
}

/**
 * writeChar - writes the character like putchar
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeChar(char c)
{
    return (write(1, &c, 1));
}

/**
 * displayString - similar to puts in C
 * @str: a pointer the integer we want to set to 402
 *
 * Return: void
 */
void displayString(char *str)
{
    while (*str != '\0')
    {
        writeChar(*str);
        str++;
    }
}

/**
 * getStringLength - Get string length.
 * @str: The string.
 * Return: Length of the string.
 */
int getStringLength(char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
        ;

    return (i);
}

/**
 * concatenateStrings - concatenate strings.
 * @s1: string.
 * @s2: second string.
 * Return: concatenated strings.
 */
char *concatenateStrings(char *s1, char *s2)
{
    char *result;
    int lenS1, lenS2, j, i, e;

    if (s1 == NULL)
        s1 = "";

    if (s2 == NULL)
        s2 = "";

    lenS1 = getStringLength(s1);

    lenS2 = getStringLength(s2);

    result = malloc(((lenS1) + (lenS2) + 1) * sizeof(char));

    if (result == NULL)
        return (NULL);

    for (j = 0; j < lenS1; j++)
    {
        result[j] = s1[j];
    }

    for (i = lenS1, e = 0; e <= lenS2; i++, e++)
    {
        result[i] = s2[e];
    }
    return result;
}
