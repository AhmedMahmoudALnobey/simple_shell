// newheader.h

#ifndef _NEWHEADER_H_
#define _NEWHEADER_H_

#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

extern char **environ;

char *getUserInput(void);
void displayPrompt(void);
char *_strConcat(char *src);
int _strLength(char *str);
void printChar(char c);
void printString(char *str);
char *findFile(char *command);
char *locateCommandInPath(char *command);
int compareStrings(char *s1, char *s2);
int compareDirectoryStrings(char *s1, char *s2);
char *concatenateStrings(char *s1, char *s2);
int checkForSlash(char *cmd);
int compareExitStrings(char *s1, char *s2);
int compareEnvStrings(char *s1, char *s2);
void performExecution(char **cmd);
char **tokenizeString(char *parameter);
void handleControlC(int sig);

#endif
