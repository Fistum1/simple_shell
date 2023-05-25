#include "shell.h"

/**
 * hsh - The main shell loop
 * 
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info1, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info1);
		if (interactive(info1))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info1);
		if (r != -1)
		{
			set_info(info1, av);
			builtin_ret = find_builtin(info1);
			if (builtin_ret == -1)
				find_cmd(info1);
		}
		else if (interactive(info1))
			_putchar('\n');
		free_info(info1, 0);
	}
	write_history(info1);
	free_info(info1, 1);
	if (!interactive(info1) && info1->status)
		exit(info1->status);
	if (builtin_ret == -2)
	{
		if (info1->err_num == -1)
			exit(info1->status);
		exit(info1->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - It finds a builtin command
 * 
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info1)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info1->argv[0], builtintbl[i].type) == 0)
		{
			info1->line_count++;
			built_in_ret = builtintbl[i].func(info1);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - It finds a command in PATH
 * 
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info1)
{
	char *path = NULL;
	int i, k;

	info1->path = info1->argv[0];
	if (info1->linecount_flag == 1)
	{
		info1->line_count++;
		info1->linecount_flag = 0;
	}
	for (i = 0, k = 0; info1->arg[i]; i++)
		if (!is_delim(info1->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info1, _getenv(info1, "PATH="), info1->argv[0]);
	if (path)
	{
		info1->path = path;
		fork_cmd(info1);
	}
	else
	{
		if ((interactive(info1) || _getenv(info1, "PATH=")
			|| info1->argv[0][0] == '/') && is_cmd(info1, info1->argv[0]))
			fork_cmd(info1);
		else if (*(info1->arg) != '\n')
		{
			info1->status = 127;
			print_error(info1, "not found\n");
		}
	}
}

/**
 * fork_cmd - It forks a an exec thread to run cmd
 * 
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info1)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info1->path, info1->argv, get_environ(info1)) == -1)
		{
			free_info(info1, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(info1->status));
		if (WIFEXITED(info1->status))
		{
			info1->status = WEXITSTATUS(info1->status);
			if (info1->status == 126)
				print_error(info1, "Permission denied\n");
		}
	}
}
