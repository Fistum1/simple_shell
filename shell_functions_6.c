#include "shell.h"

/**
 **_strncpy - It copies a string var.
 *@dest: The destination string to be copied.
 *@src: The source string.
 *@n: The amount of characters.
 *Return: the string
 */
char *_strncpy(char *dest1, char *src1, int n)
{
	int i, j;
	char *s1 = dest1;

	i = 0;
	while (src1[i] != '\0' && i < n - 1)
	{
		dest1[i] = src1[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest1[j] = '\0';
			j++;
		}
	}
	return (s1);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest1, char *src1, int n)
{
	int i, j;
	char *s1 = dest1;

	i = 0;
	j = 0;
	while (dest1[i] != '\0')
		i++;
	while (src1[j] != '\0' && j < n)
	{
		dest1[i] = src1[j];
		i++;
		j++;
	}
	if (j < n)
		dest1[i] = '\0';
	return (s1);
}

/**
 **_strchr - It locates a character in a string.
 *@s: The string to be parsed.
 *@c: The character to look for.
 *Return: (s) a pointer to the memory area s.
 */
char *_strchr(char *s1, char c1)
{
	do {
		if (*s1 == c1)
			return (s1);
	} while (*s1++ != '\0');

	return (NULL);
}
