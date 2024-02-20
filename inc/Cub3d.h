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

# define DEF_TEXT_NO "./img/default/bloody_wall_01.png"
# define DEF_TEXT_SO "./img/default/bloody_wall_02.png"
# define DEF_TEXT_WE "./img/default/brown_wall.png"
# define DEF_TEXT_EA "./img/default/brown_wall_light_cropped.png"
# define DEF_COL_FL 0x8C3B0CFF
# define DEF_COL_CE 0x5BACF5FF

# define SUCCESS 0
# define FAILURE 1

typedef struct s_cub3d
{
	char	**map;
	char	*text_no;
	char	*text_so;
	char	*text_we;
	char	*text_ea;
	int32_t	col_fl;
	int32_t	col_ce;
	// t_tex tex;
}	t_cub3d;

int		parser(int fd, t_cub3d *info);

void	cbd_free_info(t_cub3d *info);
void	print_info(t_cub3d *info);

#endif // !CUB3D_H
