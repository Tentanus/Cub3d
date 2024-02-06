#include <stdio.h>

#include "Cub3d.h"
#include "libft.h"

#include "Cub3d_error.h"

bool checkInput(int argc, char **argv)
{
	if (argc != 2)
		return (cbderror(ERR_ARGUMENT), true);
	(void)argc;
	(void)argv;
	return (false);
}

int main(int argc, char *argv[])
{
	if (checkInput(argc, argv))
		return (1);
	(void)argc;
	(void)argv;

	return (1);
}
