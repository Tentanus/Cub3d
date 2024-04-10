/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_player.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 15:36:03 by mweverli      #+#    #+#                 */
/*   Updated: 2024/03/20 15:36:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "CBDminimap.h"
#include "Cub3d.h"

static void	player_to_window(t_minimap *mini, double x, double y)
{
	const double	r = mini->player_size;
	double			i;
	double			j;

	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if ((i * i) + (j * j) <= (r * r))
				mlx_put_pixel(mini->minimap, x + i, y + j, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

static void	direction_to_window(t_minimap *mini, double x, double y, \
								t_vector_2d d)
{
	int			i;
	const int	len = mini->tile_size;

	i = 0;
	while (i <= len)
	{
		mlx_put_pixel(mini->minimap, x + (d.x * i), y + (d.y * i), \
				0xFF0000FF);
		mlx_put_pixel(mini->minimap, x + (d.x * i) + 1, y + (d.y * i) + 1, \
				0xFF0000FF);
		i++;
	}
}

void	fill_player(t_minimap *mini, t_raycaster *raycaster)
{
	const uint32_t	tile = mini->tile_size;
	const double	mini_pos_x = ((raycaster->player_pos.x) * tile);
	const double	mini_pos_y = ((raycaster->player_pos.y) * tile);

	player_to_window(mini, mini_pos_x, mini_pos_y);
	direction_to_window(mini, mini_pos_x, mini_pos_y, raycaster->player_dir);
}
