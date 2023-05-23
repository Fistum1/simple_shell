#include "shell.h"

/**
 * main - The simple Shell Project.
 * @ac: The main function parameter arg count.
 * @av:  The main function parameter arg vector.
 * Return: 0 for success, 1 for error.
 */
int main(int ab1, char **ac1)
{
	info_t it[] = { INFO_INIT };
	int id1 = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (id1)
		: "r" (id1));

	if (ab1 == 2)
	{
		id1 = open(ac1[1], O_RDONLY);
		if (id1 == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(ac1[0]);
				_eputs(": 0: Can't open ");
				_eputs(ab1[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		it->readfd = id1;
	}
	populate_env_list(it);
	read_history(it);
	hsh(it, ab1);
	return (EXIT_SUCCESS);
}
