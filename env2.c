#include "my_shell.h"

/**
 * copy_environment - Returns the string array copy of our environment
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
char **copy_environment(CommandInfo_t *info)
{
    if (!info->environment || info->env_changed)
    {
        info->environment = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environment);
}

/**
 * remove_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @variable: The string environment variable property.
 *
 * Return: 1 on delete, 0 otherwise
 */
int remove_environment_variable(CommandInfo_t *info, char *variable)
{
    StringList_t *node = info->environment;
    size_t i = 0;
    char *p;

    if (!node || !variable)
        return 0;

    while (node)
    {
        p = starts_with(node->str, variable);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->environment;
            continue;
        }
        node = node->next;
        i++;
    }

    return info->env_changed;
}

/**
 * set_environment_variable - Initialize a new environment variable,
 *                           or modify an existing one
 * @info: Structure containing potential arguments.
 * @variable: The string environment variable property.
 * @value: The string environment variable value.
 *
 * Return: Always 0
 */
int set_environment_variable(CommandInfo_t *info, char *variable, char *value)
{
    char *buffer = NULL;
    StringList_t *node;
    char *p;

    if (!variable || !value)
        return 0;

    buffer = malloc(my_strlen(variable) + my_strlen(value) + 2);
    if (!buffer)
        return 1;

    my_strcpy(buffer, variable);
    my_strcat(buffer, "=");
    my_strcat(buffer, value);

    node = info->environment;
    while (node)
    {
        p = starts_with(node->str, variable);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buffer;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }

    add_node_end(&(info->environment), buffer, 0);
    free(buffer);
    info->env_changed = 1;
    return 0;
}
