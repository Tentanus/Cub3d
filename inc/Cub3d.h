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

typedef struct s_map
{
	char	**map;				// lines are filled with ' ' to make the map rectangular
	int		px;					// index, the 'x' of the player spawn
	int		py;					// index, the 'y' of the player spawn
	char	player_direction;	// the direction the player faces in at spawn
	int		max_x;				// index, the length of the longest line in the map
	int		max_y;				// index, the number of lines in the map
	bool	map_invalid;		// set to true after floodfill confirms the map is not (fully) enclosed by walls
	bool	map_complete;		// set to true when the map is fully floodfilled
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
	mlx_t		*mlx;
	mlx_image_t	*image;
	int32_t		col_fl;
	int32_t		col_ce;

	double		px;
	double		py;
	// double		
	// double		
	// double		
	// double		
	
}	t_raycast;

typedef struct s_cub3d
{
	t_map		*chart;
	t_param		*par;
	t_raycast	*ray;
}	t_cub3d;

bool	parser(int fd, t_cub3d *info);

void	cbd_free_info(t_cub3d *info);
void	print_info(t_cub3d *info);
void	print_map(char **map);

bool	raycaster(t_cub3d *info);

#endif // !CUB3D_H
