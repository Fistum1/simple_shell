#include "shell.h"

/**
 * get_environ - It returns the string array copy of our environment.
 * @info: The structure containing potential arguments. It used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info1)
{
	if (!info1->environ || info1->env_changed)
	{
		info1->environ = list_to_strings(info1->env);
		info1->env_changed = 0;
	}

	return (info1->environ);
}

/**
 * _unsetenv - It removes an environment variable.
 * @info: The structure containing potential arguments. It used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise.
 * @var: the string env var property.
 */
int _unsetenv(info_t *info1, char *var)
{
	list_t *node = info1->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info1->env_changed = delete_node_at_index(&(info1->env), i);
			i = 0;
			node = info1->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info1->env_changed);
}

/**
 * _setenv - It initialize a new environment variable, or modify an existing one
 * @info: The structure containing potential arguments. It used to maintain
 *        constant function prototype.
 * @var: The string env var property.
 * @value: The string env var value.
 *  Return: Always 0
 */
int _setenv(info_t *info1, char *var, char *value)
{
	char *buf1 = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf1 = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf1)
		return (1);
	_strcpy(buf1, var);
	_strcat(buf1, "=");
	_strcat(buf1, value);
	node = info1->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf1;
			info1->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info1->env), buf1, 0);
	free(buf1);
	info1->env_changed = 1;
	return (0);
}
