#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42.h"
#include "libft.h"

#include "CBDerror.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define DEF_TEXT_NO "./img/default/bloody_wall_01.png"
#define DEF_TEXT_SO "./img/default/bloody_wall_02.png"
#define DEF_TEXT_WE "./img/default/brown_wall.png"
#define DEF_TEXT_EA "./img/default/brown_wall_light_cropped.png"
#define DEF_COL_FL 0xFF8C3B0C
#define DEF_COL_CE 0xFF5BACF5

#define SUCCESS 0
#define FAILURE 1

typedef struct s_cub3d
{
	char **map;
	char *text_no;
	char *text_so;
	char *text_we;
	char *text_ea;
	int32_t col_fl;
	int32_t col_ce;
	// t_tex tex;

} t_cub3d;

int parser(int fd, t_cub3d *info);
void show_info(t_cub3d *info);

#endif // !CUB3D_H
