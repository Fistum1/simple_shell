#include "shell.h"

/**
 * bfree - It frees a pointer and NULLs the address.
 * @ptr: The address of the pointer to free.
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * is_cmd - It determines if a file is an executable command.
 * @info: The info struct.
 * @path: The path to the file.
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info1, char *path)
{
	struct stat st;

	(void)info1;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - The duplicates characters.
 * @pathstr: The PATH string.
 * @start: A starting index.
 * @stop: A stopping index.
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start1, int stop1)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start1; i < stop1; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - It finds this cmd in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The cmd to find.
 * Return: The full path of cmd if found or NULL.
 */
char *find_path(info_t *info1, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info1, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info1, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
