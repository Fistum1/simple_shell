#include "shell.h"

/**
 * _erratoi - It converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise -1 on error.
 */
int _erratoi(char *s1)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s1 == '+')
		s1++;  
	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] >= '0' && s1[i] <= '9')
		{
			result *= 10;
			result += (s1[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info1, char *estr)
{
	_eputs(info1->fname);
	_eputs(": ");
	print_d(info1->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info1->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_d(int input1, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input1 < 0)
	{
		_abs_ = -input1;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input1;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - It converters function, a clone of itoa.
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num1, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num1;

	if (!(flags & CONVERT_UNSIGNED) && num1 < 0)
	{
		n = -num1;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
