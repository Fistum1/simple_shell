#include "shell.h"

/**
 * **strtow - It splits a string into words. Repeat delimiters are ignored.
 * @str: The input string.
 * @d: The delimeter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **strtow(char *str1, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s1;

	if (str1 == NULL || str1[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str1[i] != '\0'; i++)
		if (!is_delim(str1[i], d) && (is_delim(str1[i + 1], d) || !str1[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s1 = malloc((1 + numwords) * sizeof(char *));
	if (!s1)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str1[i], d))
			i++;
		k = 0;
		while (!is_delim(str1[i + k], d) && str1[i + k])
			k++;
		s1[j] = malloc((k + 1) * sizeof(char));
		if (!s1[j])
		{
			for (k = 0; k < j; k++)
				free(s1[k]);
			free(s1);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s1[j][m] = str1[i++];
		s1[j][m] = 0;
	}
	s1[j] = NULL;
	return (s1);
}

/**
 * **strtow2 - It splits a string into words.
 * @str: The input string.
 * @d: The delimeter.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow2(char *str1, char d)
{
	int i, j, k, m, numwords = 0;
	char **s1;

	if (str1 == NULL || str1[0] == 0)
		return (NULL);
	for (i = 0; str1[i] != '\0'; i++)
		if ((str1[i] != d && str1[i + 1] == d) ||
			(str1[i] != d && !str1[i + 1]) || str1[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s1 = malloc((1 + numwords) * sizeof(char *));
	if (!s1)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str1[i] == d && str1[i] != d)
			i++;
		k = 0;
		while (str1[i + k] != d && str1[i + k] && str1[i + k] != d)
			k++;
		s1[j] = malloc((k + 1) * sizeof(char));
		if (!s1[j])
		{
			for (k = 0; k < j; k++)
				free(s1[k]);
			free(s1);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s1[j][m] = str1[i++];
		s1[j][m] = 0;
	}
	s1[j] = NULL;
	return (s1);
}
