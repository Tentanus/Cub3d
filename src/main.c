#include <stdio.h>

#include "Cub3d.h"
#include "libft.h"

int main(int argc, char *argv[])
{

	for (size_t i = 0; i <= (size_t)argc; i++)
	{
		if (i != (size_t)argc)
			ft_memmove(argv[i], &argv[i][1], ft_strlen(argv[i]));
		printf("[%zu] :\t%s\n", i, argv[i]);
	}
	return (1);
}
