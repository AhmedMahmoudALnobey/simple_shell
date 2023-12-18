// modprompt.c

#include "newheader.h"

/**
 * runShellPrompt - call prompt from another function (prompt)
 **/
void runShellPrompt(void)
{
    for (;;)
    {
        char *inputText = NULL;
        pid_t childPid;
        int status, lenBuf;
        size_t bufSize = 0;

        displayPrompt();
        lenBuf = getline(&inputText, &bufSize, stdin);
        if (lenBuf == -1)
            exit(98);
        if (compareExit(inputText, "exit") == 0)
            exit(0);
        if (compareEnv(inputText, "env") == 0)
        {
            while (*environ != NULL)
            {
                if (!(_strcmpdir(*environ, "USER")) ||
                    !(_strcmpdir(*environ, "LANGUAGE")) ||
                    !(_strcmpdir(*environ, "SESSION")) ||
                    !(_strcmpdir(*environ, "COMPIZ_CONFIG_PROFILE")) ||
                    !(_strcmpdir(*environ, "SHLV")) ||
                    !(_strcmpdir(*environ, "HOME")) ||
                    !(_strcmpdir(*environ, "C_IS")) ||
                    !(_strcmpdir(*environ, "DESKTOP_SESSION")) ||
                    !(_strcmpdir(*environ, "LOGNAME")) ||
                    !(_strcmpdir(*environ, "TERM")) ||
                    !(_strcmpdir(*environ, "PATH")))
                {
                    printString(*environ);
                    printChar('\n');
                }
                environ++;
            }
        }
        childPid = fork();
        if (childPid < 0)
            perror("Error");
        if (childPid == 0)
            tokenizeString(inputText);
        else
            wait(&status);
    }
}
