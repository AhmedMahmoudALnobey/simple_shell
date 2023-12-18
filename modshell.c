// modshell.c

#include "newheader.h"

/**
 * main - function with an infinite loop
 * @argc: No use
 * @argv: No use
 * Return: loop.
 **/
int main(int argc, char **argv)
{
    (void)argv;
    (void)argc;

    signal(SIGINT, handleControlC);
    runShellPrompt();
    return (0);
}
