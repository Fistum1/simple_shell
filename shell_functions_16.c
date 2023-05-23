#include "shell.h"

/**
 * _strcpy - It copies a string.
 * @dest: The destination.
 * @src: The source.
 * Return: pointer to destination
 */
char *_strcpy(char *dest1, char *src1)
{
	int i = 0;

	if (dest1 == src1 || src1 == 0)
		return (dest1);
	while (src1[i])
	{
		dest1[i] = src1[i];
		i++;
	}
	dest1[i] = 0;
	return (dest1);
}

/**
 * _strdup - It duplicates a string.
 * @str: The string to duplicate.
 * Return: The pointer to the duplicated string
 */
char *_strdup(const char *str1)
{
	int length = 0;
	char *ret;

	if (str1 == NULL)
		return (NULL);
	while (*str1++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str1;
	return (ret);
}

/**
 *_puts - It prints an input string.
 *@str: The string to be printed.
 * Return: Nothing.
 */
void _puts(char *str1)
{
	int i = 0;

	if (!str1)
		return;
	while (str1[i] != '\0')
	{
		_putchar(str1[i]);
		i++;
	}
}

/**
 * _putchar - It writes the character c to stdout.
 * @c: The character to print.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c1)
{
	static int i;
	static char buf1[WRITE_BUF_SIZE];

	if (c1 == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf1, i);
		i = 0;
	}
	if (c1 != BUF_FLUSH)
		buf1[i++] = c1;
	return (1);
}
