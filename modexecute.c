// modexecute.c

#include "newheader.h"  // Assuming you have a new header file name

/**
 * performExecution - similar to puts in C
 * @cmd: a pointer the integer we want to set to 402
 *
 * Return: void
 */
void performExecution(char **cmd)
{
    char *param = (*(cmd + 1));
    char *s, *slash = "/";
    char *o;

    char *printVar = *cmd;
    char *argv[4];

    if ((access(cmd[0], F_OK) == 0))
    {
        argv[0] = cmd[0];
        argv[1] = param;
        argv[2] = ".";
        argv[3] = NULL;

        if (execve(argv[0], argv, NULL) == -1)
        {
            perror("Error");
        }
    }
    else
    {
        o = locateCommand(printVar);

        slash = concatenateStrings(o, slash);

        s = concatenateStrings(slash, *cmd);

        argv[0] = s;
        argv[1] = param;
        argv[2] = ".";
        argv[3] = NULL;

        if (execve(argv[0], argv, NULL) == -1)
        {
            perror("Error");
        }
    }
}
