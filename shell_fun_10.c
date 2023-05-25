#include "shell.h"

/**
 * get_history_file - It gets the history file
 * 
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info1)
{
	char *buf1, *dir;

	dir = _getenv(info1, "HOME=");
	if (!dir)
		return (NULL);
	buf1 = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf1)
		return (NULL);
	buf1[0] = 0;
	_strcpy(buf1, dir);
	_strcat(buf1, "/");
	_strcat(buf1, HIST_FILE);
	return (buf1);
}

/**
 * write_history - It creates a file, or appends to an existing file
 * 
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info1)
{
	ssize_t fd1;
	char *filename = get_history_file(info1);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd1 = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd1 == -1)
		return (-1);
	for (node = info1->history; node; node = node->next)
	{
		_putsfd(node->str, fd1);
		_putfd('\n', fd1);
	}
	_putfd(BUF_FLUSH, fd1);
	close(fd1);
	return (1);
}

/**
 * read_history - It reads history from file
 * 
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info1)
{
	int i, last = 0, linecount = 0;
	ssize_t fd1, rdlen, fsize = 0;
	struct stat st;
	char *buf1 = NULL, *filename = get_history_file(info1);

	if (!filename)
		return (0);

	fd1 = open(filename, O_RDONLY);
	free(filename);
	if (fd1 == -1)
		return (0);
	if (!fstat(fd1, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf1 = malloc(sizeof(char) * (fsize + 1));
	if (!buf1)
		return (0);
	rdlen = read(fd1, buf1, fsize);
	buf1[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf1), 0);
	close(fd1);
	for (i = 0; i < fsize; i++)
		if (buf1[i] == '\n')
		{
			buf1[i] = 0;
			build_history_list(info1, buf1 + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info1, buf1 + last, linecount++);
	free(buf1);
	info1->histcount = linecount;
	while (info1->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info1->history), 0);
	renumber_history(info1);
	return (info1->histcount);
}

/**
 * build_history_list - It adds entry to a history linked list
 * 
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info1, char *buf1, int linecount)
{
	list_t *node = NULL;

	if (info1->history)
		node = info1->history;
	add_node_end(&node, buf1, linecount);

	if (!info1->history)
		info1->history = node;
	return (0);
}

/**
 * renumber_history - It renumbers the history linked list after changes
 * 
 * @info: Structure containing potential arguments. Used to maintain
 * Return: the new histcount
 */
int renumber_history(info_t *info1)
{
	list_t *node = info1->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info1->histcount = i);
}
