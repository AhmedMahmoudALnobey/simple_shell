#include "my_shell.h"

/**
 * print_error_string - Prints an error string
 * @error_str: The string to be printed
 *
 * Return: Nothing
 */
void print_error_string(char *error_str)
{
    int i = 0;

    if (!error_str)
        return;

    while (error_str[i] != '\0')
    {
        print_error_char(error_str[i]);
        i++;
    }
}

/**
 * print_error_char - Writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_error_char(char c)
{
    static int i;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
    {
        write(2, buffer, i);
        i = 0;
    }

    if (c != FLUSH_BUFFER)
        buffer[i++] = c;

    return 1;
}

/**
 * write_to_fd - Writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_to_fd(char c, int fd)
{
    static int i;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
    {
        write(fd, buffer, i);
        i = 0;
    }

    if (c != FLUSH_BUFFER)
        buffer[i++] = c;

    return 1;
}

/**
 * print_string_to_fd - Prints an input string to the specified file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int print_string_to_fd(char *str, int fd)
{
    int count = 0;

    if (!str)
        return 0;

    while (*str)
    {
        count += write_to_fd(*str++, fd);
    }

    return count;
}
