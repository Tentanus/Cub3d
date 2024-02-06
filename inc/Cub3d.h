#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42.h"
#include "libft.h"

#include "CBDerror.h"
#include "CBDparser.h"

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef LOG
#define LOG 0
#endif // !LOG

#define SUCCESS 0
#define FAILURE 1

typedef struct s_cub3d
{
	char **map;
	// t_tex tex;

} t_cub3d;

int parser(int fd, t_cub3d *info);

#endif // !CUB3D_H
