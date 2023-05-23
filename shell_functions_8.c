#include "shell.h"

/**
 * clear_info - It initializes info_t struct.
 * @info: The struct address.
 */
void clear_info(info_t *info1)
{
	info1->arg = NULL;
	info1->argv = NULL;
	info1->path = NULL;
	info1->argc = 0;
}

/**
 * set_info - It initializes info_t struct.
 * @info: The struct address.
 * @av: An argument vector.
 */
void set_info(info_t *info1, char **av)
{
	int i = 0;

	info1->fname = av[0];
	if (info1->arg)
	{
		info1->argv = strtow(info1->arg, " \t");
		if (!info1->argv)
		{

			info1->argv = malloc(sizeof(char *) * 2);
			if (info1->argv)
			{
				info1->argv[0] = _strdup(info1->arg);
				info1->argv[1] = NULL;
			}
		}
		for (i = 0; info1->argv && info1->argv[i]; i++)
			;
		info1->argc = i;

		replace_alias(info1);
		replace_vars(info1);
	}
}

/**
 * free_info - A free info_t struct fields
 * @info: The struct address.
 * @all: A true if freeing all fields.
 */
void free_info(info_t *info1, int all)
{
	ffree(info1->argv);
	info1->argv = NULL;
	info1->path = NULL;
	if (all)
	{
		if (!info1->cmd_buf)
			free(info1->arg);
		if (info1->env)
			free_list(&(info1->env));
		if (info1->history)
			free_list(&(info1->history));
		if (info1->alias)
			free_list(&(info1->alias));
		ffree(info1->environ);
		info1->environ = NULL;
		bfree((void **)info1->cmd_buf);
		if (info1->readfd > 2)
			close(info1->readfd);
		_putchar(BUF_FLUSH);
	}
}
