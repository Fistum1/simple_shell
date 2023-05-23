#include "shell.h"

/**
 * _strlen - It returns the length of a string.
 * @s: The string whose length to check.
 *
 * Return: The integer length of string.
 */
int _strlen(char *s1)
{
	int i = 0;

	if (!s1)
		return (0);

	while (*s1++)
		i++;
	return (i);
}

/**
 * _strcmp - It performs lexicogarphic comparison of two strangs.
 * @s1: The first strang.
 * @s2: The second strang.
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int _strcmp(char *s11, char *s22)
{
	while (*s11 && *s22)
	{
		if (*s11 != *s22)
			return (*s11 - *s22);
		s11++;
		s22++;
	}
	if (*s11 == *s22)
		return (0);
	else
		return (*s11 < *s22 ? -1 : 1);
}

/**
 * starts_with - It checks if needle starts with haystack.
 * @haystack: It string to search.
 * @needle: The substring to find.
 * Return: The address of next char of haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - It concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 * Return: The pointer to destination buffer.
 */
char *_strcat(char *dest1, char *src1)
{
	char *ret = dest1;

	while (*dest1)
		dest1++;
	while (*src1)
		*dest1++ = *src1++;
	*dest1 = *src1;
	return (ret);
}
