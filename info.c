#include "my_shell.h"

/**
 * initialize_info - initializes info_t struct
 * @info: struct address
 */
void initialize_info(info_t *info)
{
	info->argument_line = NULL;
	info->argument_vector = NULL;
	info->command_path = NULL;
	info->argument_count = 0;
}

/**
 * populate_info - populates info_t struct
 * @info: struct address
 * @program_arguments: argument vector
 */
void populate_info(info_t *info, char **program_arguments)
{
	int i = 0;

	info->program_name = program_arguments[0];
	if (info->argument_line)
	{
		info->argument_vector = strtow(info->argument_line, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->argument_line);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info_struct - frees info_t struct fields
 * @info: struct address
 * @free_all: true if freeing all fields
 */
void free_info_struct(info_t *info, int free_all)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->command_path = NULL;
	if (free_all)
	{
		if (!info->command_buffer)
			free(info->argument_line);
		if (info->environment)
			free_list(&(info->environment));
		if (info->command_history)
			free_list(&(info->command_history));
		if (info->alias_list)
			free_list(&(info->alias_list));
		ffree(info->environ_copy);
		info->environ_copy = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}
