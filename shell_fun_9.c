#include "shell.h"

/**
 * input_buf - It buffers chained commands
 * 
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info1, char **buf1, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		
		free(*buf1);
		*buf1 = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info1, buf1, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf1)[r - 1] == '\n')
			{
				(*buf1)[r - 1] = '\0'; 
				r--;
			}
			info1->linecount_flag = 1;
			remove_comments(*buf1);
			build_history_list(info1, *buf1, info1->histcount++);
			
			{
				*len = r;
				info1->cmd_buf = buf1;
			}
		}
	}
	return (r);
}

/**
 * get_input - It gets a line minus the newline
 * 
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info1)
{
	static char *buf1; 
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info1->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info1, &buf1, &len);
	if (r == -1) 
		return (-1);
	if (len)	
	{
		j = i; 
		p = buf1 + i; 

		check_chain(info1, buf1, &j, i, len);
		while (j < len) 
		{
			if (is_chain(info1, buf1, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len) 
		{
			i = len = 0; 
			info1->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (_strlen(p)); 
	}

	*buf_p = buf1; 
	return (r); 
}

/**
 * read_buf - It reads a buffer
 * 
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info1, char *buf1, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info1->readfd, buf1, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - It gets the next line of input from STDIN
 * 
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info1, char **ptr, size_t *length)
{
	static char buf1[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c1;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info1, buf1, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c1 = _strchr(buf1 + i, '\n');
	k = c1 ? 1 + (unsigned int)(c1 - buf1) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf1 + i, k - i);
	else
		_strncpy(new_p, buf1 + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - It blocks ctrl-C
 * 
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
