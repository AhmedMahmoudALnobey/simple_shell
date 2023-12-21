#include "my_shell.h"

/**
 * get_shell_history_file - gets the shell history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_shell_history_file(info_t *info)
{
    char *home_dir, *file_path;

    home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return NULL;

    file_path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
    if (!file_path)
        return NULL;

    file_path[0] = 0;
    _strcpy(file_path, home_dir);
    _strcat(file_path, "/");
    _strcat(file_path, HIST_FILE);

    return file_path;
}

/**
 * write_shell_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_shell_history(info_t *info)
{
    ssize_t fd;
    char *file_name = get_shell_history_file(info);
    list_t *node = NULL;

    if (!file_name)
        return -1;

    fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(file_name);

    if (fd == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        print_string_to_fd(node->str, fd);
        _putfd('\n', fd);
    }

    _putfd(FLUSH_BUFFER, fd);
    close(fd);

    return 1;
}

/**
 * read_shell_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_shell_history(info_t *info)
{
    int i, last = 0, line_count = 0;
    ssize_t fd, read_len, file_size = 0;
    struct stat st;
    char *buffer = NULL, *file_name = get_shell_history_file(info);

    if (!file_name)
        return 0;

    fd = open(file_name, O_RDONLY);
    free(file_name);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        file_size = st.st_size;

    if (file_size < 2)
        return 0;

    buffer = malloc(sizeof(char) * (file_size + 1));
    if (!buffer)
        return 0;

    read_len = read(fd, buffer, file_size);
    buffer[file_size] = 0;

    if (read_len <= 0)
        return free(buffer), 0;

    close(fd);

    for (i = 0; i < file_size; i++)
        if (buffer[i] == '\n')
        {
            buffer[i] = 0;
            build_shell_history_list(info, buffer + last, line_count++);
            last = i + 1;
        }

    if (last != i)
        build_shell_history_list(info, buffer + last, line_count++);

    free(buffer);
    info->histcount = line_count;

    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_shell_history(info);

    return info->histcount;
}

/**
 * build_shell_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @line_count: the history line count, histcount
 *
 * Return: Always 0
 */
int build_shell_history_list(info_t *info, char *buf, int line_count)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_node_end(&node, buf, line_count);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_shell_history - renumbers the shell history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_shell_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return info->histcount = i;
}
