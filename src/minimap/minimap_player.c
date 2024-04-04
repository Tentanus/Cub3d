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

void	player_to_window(t_minimap *mini, double x, double y, double r)
{
	double	i;
	double	j;

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

void	fill_player(t_minimap *mini, t_raycaster *raycaster)
{
	const uint32_t	tile = mini->tile_size;
	const double	mini_pos_x = ((raycaster->player_pos.x) * tile);
	const double	mini_pos_y = ((raycaster->player_pos.y) * tile);

	player_to_window(mini, mini_pos_x, mini_pos_y, mini->player_size);
}
