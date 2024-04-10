/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:46:31 by mweverli          #+#    #+#             */
/*   Updated: 2024/03/25 14:48:34 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <fcntl.h>				//	open
# include <stdio.h>				//	printf
# include <stdlib.h>			//	malloc, free, exit
# include <unistd.h>			//	close, read, write

// from math.h
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */
# define M_1_PI		0.31830988618379067154	/* 1/pi */
# define M_2_PI		0.63661977236758134308	/* 2/pi */
# define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */

# include "MLX42.h"
# include "libft.h"

# include "CBDerror.h"
# include "CBDparser.h"
# include "CBDraycaster.h"

# define WINDOW_HEIGHT 720
# define WINDOW_WIDTH 1280

# define MINIMAP_SIZE_MOD 2
# define MINIMAP_BORDER 2

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
	double	x;
	double	y;
}	t_vector_2d;

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

typedef struct s_minimap
{
	mlx_image_t	*minimap;
	uint32_t	tile_size;
	uint32_t	player_size;
	uint32_t	dimention_x;
	uint32_t	dimention_y;
}	t_minimap;

typedef struct s_raycaster
{
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_texture_t	*textures[4];
	int32_t			col_fl;
	int32_t			col_ce;

	char			**map;

	t_vector_2d player_pos;
	t_vector_2d	player_dir;
	t_vector_2d	plane;
	double		move_speed;
	// t_vector_2d
}	t_raycaster;

typedef struct s_ray
{
	t_vector_2d	start_pos;  //x and y start position
	t_vector_2d	start_dir;	//initial direction vector
	t_vector_2d	plane;		//the 2d raycaster version of camera plane
	t_vector_2d	map; 		//which box of the map we're in
	t_vector_2d side_dist;	//length of ray from current position to next x or y-side
	t_vector_2d	delta_dist;	//length of ray from one x or y-side to next x or y-side
	t_vector_2d	step;		//what direction to step in x or y-direction (either +1 or -1)

	double		camera_x;
	double		perp_dist;	//distance of perpendicular ray (Euclidean distance would give fisheye effect!)
	bool		hit;		//was there a wall hit?
	int			side;		//was a NS or a EW wall hit? (can be developed to figur out which side between NS/EW)
}	t_ray;

typedef struct s_cub3d
{
	t_map		*chart;
	t_param		*param;
	t_raycaster	*raycaster;
	t_minimap	*minimap;
}	t_cub3d;

bool	parser(int fd, t_cub3d *info);
bool	raycaster(t_cub3d *info);

void	cub3d_key_hook(mlx_key_data_t keydata, void *param);

void	cbd_free_info(t_cub3d *info);

// Functions to be removed:  TODO:

void	minimap_hook(void *param);
void	print_info(t_cub3d *info);
void	print_map(char **map);


#endif // !CUB3D_H
