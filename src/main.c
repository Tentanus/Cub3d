#include <stdio.h>

#include "Cub3d.h"
#include "libft.h"

int checkInput(int argc, char **argv)
{
	int fd;
	size_t filenameLength;

	if (argc != 2)
		return (cbdError(ERR_ARGUMENT), -1);
	filenameLength = ft_strlen(argv[1]);
	if (filenameLength <= 4 ||
		ft_strncmp(&argv[1][filenameLength - 4], ".cub", 5))
		return (cbdError(ERR_SUFFIX), -1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (cbdError(ERR_FILE), -1);
	return (fd);
}

int main(int argc, char *argv[])
{
	if (parser(checkInput(argc, argv)))
		return (FAILURE);

	return (SUCCESS);
}
