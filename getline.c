#include "my_shell.h"

/**
 * buffer_chained_commands - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t buffer_chained_commands(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		read_bytes = getline(buf, &len_p, stdin);
#else
		read_bytes = _getline(info, buf, &len_p);
#endif
		if (read_bytes > 0)
		{
			if ((*buf)[read_bytes - 1] == '\n')
			{
				(*buf)[read_bytes - 1] = '\0'; /* remove trailing newline */
				read_bytes--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_shell_history_list(info, *buf, info->histcount++);
			{
				*len = read_bytes;
				info->cmd_buf = buf;
			}
		}
	}
	return (read_bytes);
}

/**
 * get_input_line - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input_line(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t read_bytes = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	read_bytes = buffer_chained_commands(info, &buf, &len);
	if (read_bytes == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (read_bytes); /* return length of buffer from _getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t read_bytes = 0;

	if (*i)
		return (0);
	read_bytes = read(info->readfd, buf, READ_BUF_SIZE);
	if (read_bytes >= 0)
		*i = read_bytes;
	return (read_bytes);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_bytes = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (i == len)
		i = len = 0;

	read_bytes = read_buffer(info, buf, &len);
	if (read_bytes == -1 || (read_bytes == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, size, size ? size + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (size)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	size += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return (size);
}

/**
 * handle_sigint - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
