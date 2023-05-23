#include "shell.h"

/**
 * _myhistory - It displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: The structure containing potential arguments. It used to maintain and
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info1)
{
	print_list(info1->history);
	return (0);
}

/**
 * unset_alias - It sets alias to string.
 * @info: parameter struct
 * @str: string alias
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info1, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info1->alias),
		get_node_index(info1->alias, node_starts_with(info1->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - It sets alias to string.
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info1, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info1, str));

	unset_alias(info1, str);
	return (add_node_end(&(info1->alias), str, 0) == NULL);
}

/**
 * print_alias - It prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - It mimics the alias builtin (man alias)
 * @info: The structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info1)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info1->argc == 1)
	{
		node = info1->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info1->argv[i]; i++)
	{
		p = _strchr(info1->argv[i], '=');
		if (p)
			set_alias(info1, info1->argv[i]);
		else
			print_alias(node_starts_with(info1->alias, info1->argv[i], '='));
	}

	return (0);
}
