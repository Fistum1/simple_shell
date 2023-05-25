#include "shell.h"

/**
 *_eputs - It prints an input string

 * @str: the string to be printed
 * Return: Nothing
 * 
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - It writes the character c to stderr
 * 
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 * 
 */
int _eputchar(char c1)
{
	static int i;
	static char buf1[WRITE_BUF_SIZE];

	if (c1 == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf1, i);
		i = 0;
	}
	if (c1 != BUF_FLUSH)
		buf1[i++] = c1;
	return (1);
}

/**
 * _putfd - It writes the character c to given fd
 * 
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 * 
 */
int _putfd(char c1, int fd1)
{
	static int i;
	static char buf1[WRITE_BUF_SIZE];

	if (c1 == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd1, buf1, i);
		i = 0;
	}
	if (c1 != BUF_FLUSH)
		buf1[i++] = c1;
	return (1);
}

/**
 *_putsfd - It prints an input string
 *
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 * 
 */
int _putsfd(char *str, int fd1)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd1);
	}
	return (i);
}
/**
 * remove_comments - It function replaces first instance of '#' with '\0'
 * 
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 * 
 */
void remove_comments(char *buf1)
{
	int i;

	for (i = 0; buf1[i] != '\0'; i++)
		if (buf1[i] == '#' && (!i || buf1[i - 1] == ' '))
		{
			buf1[i] = '\0';
			break;
		}
}
