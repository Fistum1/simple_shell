#include "shell.h"
/**
 *_myexit - It will exit the shell
 *@info: The structure containing potential arguments. It used to maintain.
 *Return: It exits with a given exit status.
 */
int _myexit(info_t *info1)
{
	int exitcheck;

	if (info1->argv[1])  
	{
		exitcheck = _erratoi(info1->argv[1]);
		if (exitcheck == -1)
		{
			info1->status = 2;
			print_error(info1, "Illegal number: ");
			_eputs(info1->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info1->err_num = _erratoi(info1->argv[1]);
		return (-2);
	}
	info1->err_num = -1;
	return (-2);
}

/**
*_mycd- It changes the current directory of the process.
*@info: The structure containing potential arguments. It used to maintain.
*Return: Always 0
*/
int _mycd(info_t *info1)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info1->argv[1])
	{
		dir = _getenv(info1, "HOME=");
		if (!dir)
			chdir_ret = 
			chdir((dir = _getenv(info1, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info1->argv[1], "-") == 0)
	{
		if (!_getenv(info1, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info1, "OLDPWD=")), _putchar('\n');
		chdir_ret = 
			chdir((dir = _getenv(info1, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info1->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info1, "can't cd to ");
		_eputs(info1->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info1, "OLDPWD", _getenv(info1, "PWD="));
		_setenv(info1, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - It changes the current directory of the process.
 * @info: The structure containing potential arguments.
 * Return: 0
 */
int _myhelp(info_t *info1)
{
	char **arg_array;

	arg_array = info1->argv;
	_puts("help call works. not implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
