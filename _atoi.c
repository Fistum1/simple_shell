#include "shell.h"

/**
 * interactive - It returns true if shell is interactive mode.
 * @info: The struct address.
 * Return: 1 if interactive mode, 0 otherwise.
 */
int interactive(info_t *info1)
{
	return (isatty(STDIN_FILENO) && info1->readfd <= 2);
}

/**
 * is_delim - It checks if character is a delimeter.
 * @cx: The char to check.
 * @delim: The delimeter string.
 * Return: 1 if true, 0 if false.
 */
int is_delim(char cx1, char *delim)
{
	while (*delim)
		if (*delim++ == cx1)
			return (1);
	return (0);
}

/**
 *_isalpha - It checks for alphabetic character.
 *@cx: The character to input.
 *Return: 1 if c is alphabetic, 0 otherwise.
 */

int _isalpha(int cx1)
{
	if ((cx1>= 'a' && cx1 <= 'z') || (cx1 >= 'A' && cx1<= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - It converts a string to an integer.
 *@s: The string to be converted.
 *Return: 0 if no numbers in string, converted number otherwise.
 */

int _atoi(char *sx1)
{
	int i, o;

	int	sign = 1, flag = 0;
	unsigned int results = 0;

	for (i = 0; sx1[i] != '\0' && flag != 2; i++)
	{
		if (sx1[i] == '-')
			sign *= -1;

		if (sx1[i] >= '0' && sx1[i] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (sx1[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		o = -results;
	else
		o = results;

	return (o);
}
