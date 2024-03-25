/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:46:31 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/13 19:46:33 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stdint.h>
# include <fcntl.h>				//	open
# include <stdio.h>				//	printf
# include <stdlib.h>			//	malloc, free, exit
# include <unistd.h>			//	close, read, write
# include <math.h>

# include "MLX42.h"
# include "libft.h"

# include "CBDerror.h"
# include "CBDparser.h"
# include "CBDraycaster.h"

# define WINDOW_HEIGHT 720
# define WINDOW_WIDTH 1280

# define DEF_TEXT_NO "./img/default/bloody_wall_01.png"
# define DEF_TEXT_SO "./img/default/bloody_wall_02.png"
# define DEF_TEXT_WE "./img/default/brown_wall.png"
# define DEF_TEXT_EA "./img/default/brown_wall_light_cropped.png"
# define DEF_COL_FL 0x8C3B0CFF
# define DEF_COL_CE 0x5BACF5FF

# define SUCCESS 0
# define FAILURE 1

typedef struct s_vector_2d
{
	double x;
	double y;
} t_vector_2d;

typedef struct s_map
{
	char	**map;
	int		px;			// + 0.5 to centre in tile
	int		py;
	char	player_direction;
	int		max_x;
	int		max_y;
	bool	map_invalid;
	bool	map_complete;
}	t_map;

typedef struct s_parameters
{
	char		*text_no;
	char		*text_so;
	char		*text_we;
	char		*text_ea;
	int32_t		col_fl;
	int32_t		col_ce;
}	t_param;

typedef struct s_raycaster
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*textures[4];
	int32_t			col_fl;
	int32_t			col_ce;

	t_vector_2d player_pos;
	// t_vector_2d
	// t_vector_2d
}	t_raycaster;

typedef struct s_ray
{
	double	start_x;
	double	start_y;
	double	angle;
	double	dir_x;
}	t_ray;

typedef struct s_cub3d
{
	t_map		*chart;
	t_param		*param;
	t_raycaster	*raycaster;
}	t_cub3d;

bool	parser(int fd, t_cub3d *info);

void	cbd_free_info(t_cub3d *info);
void	print_info(t_cub3d *info);
void	print_map(char **map);

bool	raycaster(t_cub3d *info);

#endif // !CUB3D_H
