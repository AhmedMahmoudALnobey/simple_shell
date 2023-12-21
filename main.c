#include "my_shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info[] = { INFO_INIT };
    int fd = STDERR_FILENO;  // Use STDERR_FILENO for file descriptor

    // Use named constant instead of magic number
    const int PERMISSION_DENIED_EXIT_CODE = 126;
    const int COMMAND_NOT_FOUND_EXIT_CODE = 127;

    // Use symbolic constant for buffer flush
    const int BUF_FLUSH = '\0';

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(PERMISSION_DENIED_EXIT_CODE);
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(COMMAND_NOT_FOUND_EXIT_CODE);
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }

    // Check for errors after these operations
    if (!populate_env_list(info) || !read_history(info))
    {
        // Handle errors and free resources if needed
        return EXIT_FAILURE;
    }

    // Main shell loop
    hah(info, av);

    // Close the file descriptor if it was opened
    if (ac == 2)
    {
        close(fd);
    }

    return EXIT_SUCCESS;
}