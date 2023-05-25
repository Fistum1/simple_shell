#include "shell.h"

/**
 * is_chain - It test if current char in buffer is a chain delimeter
 * 
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info1, char *buf1, size_t *p)
{
	size_t j = *p;

	if (buf1[j] == '|' && buf1[j + 1] == '|')
	{
		buf1[j] = 0;
		j++;
		info1->cmd_buf_type = CMD_OR;
	}
	else if (buf1[j] == '&' && buf1[j + 1] == '&')
	{
		buf1[j] = 0;
		j++;
		info1->cmd_buf_type = CMD_AND;
	}
	else if (buf1[j] == ';') 
	{
		buf1[j] = 0; 
		info1->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - It checks we should continue chaining based on last status
 * 
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info1, char *buf1, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info1->cmd_buf_type == CMD_AND)
	{
		if (info1->status)
		{
			buf1[i] = 0;
			j = len;
		}
	}
	if (info1->cmd_buf_type == CMD_OR)
	{
		if (!info1->status)
		{
			buf1[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - It replaces an aliases in the tokenized string
 * 
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info1)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info1->alias, info1->argv[0], '=');
		if (!node)
			return (0);
		free(info1->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info1->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - It replaces vars in the tokenized string
 * 
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info1)
{
	int i = 0;
	list_t *node;

	for (i = 0; info1->argv[i]; i++)
	{
		if (info1->argv[i][0] != '$' || !info1->argv[i][1])
			continue;

		if (!_strcmp(info1->argv[i], "$?"))
		{
			replace_string(&(info1->argv[i]),
				_strdup(convert_number(info1->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info1->argv[i], "$$"))
		{
			replace_string(&(info1->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info1->env, &info1->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info1->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info1->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - It replaces string
 * 
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
