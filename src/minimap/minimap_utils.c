/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 15:36:03 by mweverli      #+#    #+#                 */
/*   Updated: 2024/03/20 15:36:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "CBDminimap.h"

void	tile_to_window(t_minimap *mini, size_t x, size_t y, uint32_t col)
{
	const int32_t	tile = mini->tile_size >> 1;
	int				i;
	int				j;

	i = -tile;
	while (i <= tile)
	{
		j = -tile;
		while (j <= tile)
		{
			mlx_put_pixel(mini->minimap, \
				x + i, y + j, col);
			j++;
		}
		i++;
	}
}

void	b_tile_to_window(t_minimap *mini, size_t x, size_t y, uint32_t col)
{
	const int32_t	tile = mini->tile_size >> 1;
	int				i;
	int				j;

	i = -tile + MINIMAP_BORDER;
	while (i <= tile - MINIMAP_BORDER)
	{
		j = -tile + MINIMAP_BORDER;
		while (j <= tile - MINIMAP_BORDER)
		{
			mlx_put_pixel(mini->minimap, \
				x + i, y + j, col);
			j++;
		}
		i++;
	}
}

void	minimap_key_hook(mlx_key_data_t keydata, void *param)
{
	t_minimap	*mini;

	mini = (t_minimap *) param;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		mini->minimap->enabled = \
			ft_ternary(mini->minimap->enabled, false, true);
}
