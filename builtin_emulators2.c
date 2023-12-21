#include "my_shell.h"

/**
 * _myhistory - Displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myhistory(CommandInfo_t *info)
{
    print_list_str(info->history);
    return (0);
}

/**
 * unset_alias - Unsets alias to string
 * @info: Parameter struct
 * @str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(CommandInfo_t *info, char *str)
{
    char *p, c;
    int ret;

    p = my_strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias),
                               get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - Sets alias to string
 * @info: Parameter struct
 * @str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(CommandInfo_t *info, char *str)
{
    char *p;

    p = my_strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(StringList_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = my_strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            my_putchar(*a);
        my_putchar('\'');
        my_puts(p + 1);
        my_puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - Mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myalias(CommandInfo_t *info)
{
    int i = 0;
    char *p = NULL;
    StringList_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = my_strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
