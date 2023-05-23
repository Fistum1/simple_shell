#include "shell.h"

/**
 * list_len - It determines length of linked list.
 * @h: The pointer to first node.
 * Return: The size of list.
 */
size_t list_len(const list_t *h1)
{
	size_t i = 0;

	while (h1)
	{
		h1 = h1->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - It returns an array of strings of the list->str.
 * @head: The pointer to first node.
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str1;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str1 = malloc(_strlen(node->str) + 1);
		if (!str1)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str1 = _strcpy(str1, node->str);
		strs[i] = str1;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - It prints all elements of a list_t linked list.
 * @h: The pointer to first node.
 * Return: The size of list.
 */
size_t print_list(const list_t *h1)
{
	size_t i = 0;

	while (h1)
	{
		_puts(convert_number(h1->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h1->str ? h1->str : "(nil)");
		_puts("\n");
		h1 = h1->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - It returns node whose string starts with prefix.
 * @node: The pointer to list head.
 * @prefix: The string to match.
 * @c: The next character after prefix to match.
 * Return: It matchs node or null.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c1)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c1 == -1) || (*p == c1)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - It gets the index of a node.
 * @head: The pointer to list head.
 * @node: The pointer to the node.
 * Return: The index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
