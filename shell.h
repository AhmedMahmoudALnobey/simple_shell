#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define MY_READ_BUF_SIZE 1024
#define MY_WRITE_BUF_SIZE 1024
#define MY_BUF_FLUSH -1

/* for command chaining */
#define MY_CMD_NORM 
#define MY_CMD_OR 1
#define MY_CMD_AND 2
#define MY_CMD_CHAIN 3

/* for convert_number() */
#define MY_CONVERT_LOWERCASE 1
#define MY_CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define MY_HIST_FILE ".my_simple_shell_history"
#define MY_HIST_MAX 4096

extern char **my_environ;

/**
 * struct MyListStr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct MyListStr
{
    int num;
    char *str;
    struct MyListStr *next;
} MyList_t;

/**
 * struct MyPassInfo - contains pseudo-arguments to pass into a function,
 *                      allowing a uniform prototype for a function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct MyPassInfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    MyList_t *env;
    MyList_t *history;
    MyList_t *alias;
    char **environ;
    int env_changed;
    int status;

    char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} MyInfo_t;

#define MY_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 * struct MyBuiltin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct MyBuiltin
{
    char *type;
    int (*func)(MyInfo_t *);
} MyBuiltinTable;

/* hsh.c */
int my_hsh(MyInfo_t *, char **);
int find_my_builtin(MyInfo_t *);
void find_my_cmd(MyInfo_t *);
void fork_my_cmd(MyInfo_t *);

/* path.c */
int is_my_cmd(MyInfo_t *, char *);
char *my_dup_chars(char *, int, int);
char *find_my_path(MyInfo_t *, char *, char *);

/* loophsh.c */
int my_loophsh(char **);

/* err_string_functions.c */
void my_eputs(char *);
int my_eputchar(char);
int my_putfd(char c, int fd);
int my_putsfd(char *str, int fd);

/* string_functions.c */
int my_strlen(char *);
int my_strcmp(char *, char *);
char *my_starts_with(const char *, const char *);
char *my_strcat(char *, char *);

/* string_functions2.c */
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);

/* string_functions3.c */
char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/* string_functions4.c */
char **my_strtow(char *, char *);
char **my_strtow2(char *, char);

/* memory_functions */
char *my_memset(char *, char, unsigned int);
void my_ffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int my_bfree(void **);

/* more_functions.c */
int my_interactive(MyInfo_t *);
int my_is_delim(char, char *);
int my_isalpha(int);
int my_atoi(char *);

/* more_functions2.c */
int my_erratoi(char *);
void my_print_error(MyInfo_t *, char *);
int my_print_d(int, int);
char *my_convert_number(long int, int, int);
void my_remove_comments(char *);

/* builtin_emulators.c */
int my_myexit(MyInfo_t *);
int my_mycd(MyInfo_t *);
int my_myhelp(MyInfo_t *);

/* builtin_emulators2.c */
int my_myhistory(MyInfo_t *);
int my_myalias(MyInfo_t *);

/* getline.c module */
ssize_t my_get_input(MyInfo_t *);
int my_getline(MyInfo_t *, char **, size_t *);
void my_sigintHandler(int);

/* info.c module */
void my_clear_info(MyInfo_t *);
void my_set_info(MyInfo_t *, char **);
void my_free_info(MyInfo_t *, int);

/* env.c module */
char *my_getenv(MyInfo_t *, const char *);
int my_myenv(MyInfo_t *);
int my_mysetenv(MyInfo_t *);
int my_myunsetenv(MyInfo_t *);
int my_populate_env_list(MyInfo_t *);

/* env2.c module */
char **my_get_environ(MyInfo_t *);
int my_unsetenv(MyInfo_t *, char *);
int my_setenv(MyInfo_t *, char *, char *);

/* file_io_functions.c */
char *my_get_history_file(MyInfo_t *info);
int my_write_history(MyInfo_t *info);
int my_read_history(MyInfo_t *info);
int my_build_history_list(MyInfo_t *info, char *buf, int linecount);
int my_renumber_history(MyInfo_t *info);

/* liststr.c module */
MyList_t *my_add_node(MyList_t **, const char *, int);
MyList_t *my_add_node_end(MyList_t **, const char *, int);
size_t my_print_list_str(const MyList_t *);
int my_delete_node_at_index(MyList_t **, unsigned int);
void my_free_list(MyList_t **);

/* liststr2.c module */
size_t my_list_len(const MyList_t *);
char **my_list_to_strings(MyList_t *);
size_t my_print_list(const MyList_t *);
MyList_t *my_node_starts_with(MyList_t *, char *, char);
ssize_t my_get_node_index(MyList_t *, MyList_t *);

/* chain.c */
int my_is_chain(MyInfo_t *, char *, size_t *);
void my_check_chain(MyInfo_t *, char *, size_t *, size_t, size_t);
int my_replace_alias(MyInfo_t *);
int my_replace_vars(MyInfo_t *);
int my_replace_string(char **, char *);

#endif