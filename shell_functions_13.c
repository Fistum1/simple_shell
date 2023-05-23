#include "shell.h"

/**
 **_memset - It fills memory with a constant byte.
 *@s: The pointer to the memory area.
 *@b: The byte to fill *s with.
 *@n: The amount of bytes to be filled.
 *Return: (s) a pointer to the memory area s.
 */
char *_memset(char *s1, char b1, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s1[i] = b1;
	return (s1);
}

/**
 * ffree - It frees a string of strings.
 * @pp: The string of strings.
 */
void ffree(char **pp)
{
	char **a1 = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a1);
}

/**
 * _realloc - It reallocates a block of memory.
 * @ptr: The pointer to previous malloc'ated block.
 * @old_size: The byte size of previous block.
 * @new_size: The byte size of new block.
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p1;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p1 = malloc(new_size);
	if (!p1)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p1[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p1);
}
