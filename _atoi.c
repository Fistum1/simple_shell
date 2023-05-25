#include "shell.h"

/**
 * interactive - It returns true if shell is interactive mode
 * 
 * @info: The struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 * 
 */
int interactive(info_t *info1)
{
	return (isatty(STDIN_FILENO) && info1->readfd <= 2);
}

/**
 * is_delim - It checks if character is a delimeter
 * 
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 * 
 */
int is_delim(char c1, char *delim)
{
	while (*delim)
		if (*delim++ == c1)
			return (1);
	return (0);
}

/**
 *_isalpha - It checks for alphabetic character
 *
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 *
 */

int _isalpha(int c1)
{
	if ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - It converts a string to an integer
 *
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 *
 */

int _atoi(char *s)
{
	int i, o;

	int	sign = 1, flag = 0;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		o = -result;
	else
		o = result;

	return (o);
}
