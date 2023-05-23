#include "shell.h"

/**
 * _myunsetenv - It removes an environment variable
 * @info: The structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info1)
{
	int i;

	if (info1->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info1->argc; i++)
		_unsetenv(info1, info1->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: The structure containing potential arguments. It used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info1)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info1->env = node;
	return (0);
}

/**
 * _myenv - prints the current environment
 * @info: The structure containing potential arguments. It used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info1)
{
	print_list_str(info1->env);
	return (0);
}
/**
 * _getenv - It gets the value of an environ variable.
 * @info: The structure containing potential arguments. It used to maintain.
 * @name: env var name
 * Return: the value
 */
char *_getenv(info_t *info1, const char *name)
{
	list_t *node = info1->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - It initialize a new environment variable or modify an existing one
 * @info: The structure containing potential arguments. Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info1)
{
	if (info1->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info1, info1->argv[1], info1->argv[2]))
		return (0);
	return (1);
}

