/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_hook.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 15:36:03 by mweverli      #+#    #+#                 */
/*   Updated: 2024/03/20 15:36:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "CBDminimap.h"

void	circle_to_window(t_minimap *mini, double x, double y, double r, uint32_t col)
{
	double	i;
	double	j;
	
	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
	//		printf("pos: %d\t%d\n", x, y);
	//		printf("pxl: %d\t%d\n", (i * i) + (j * j), (r * r));
			if ((i * i) + (j * j) <= (r * r))
				mlx_put_pixel(mini->minimap, x + i, y + j, col);
			j++;
		}
		i++;
	}
}

void	square_to_window(t_minimap *mini, size_t x, size_t y, uint32_t col)
{
	const uint32_t	tile = mini->tile_size;
	size_t			i;
	size_t			j;

	i = 0;
	while (i < tile)
	{
		j = 0;
		while (j < tile)
		{
			mlx_put_pixel(mini->minimap, \
				 (x * tile) + i + (tile >> 1), (y * tile) + j + (tile >> 1), col);
			j++;
		}
		i++;
	}
}

void	tile_to_window(t_minimap *mini, size_t x, size_t y, uint32_t col)
{
	const int32_t	tile = mini->tile_size >> 1;
	int			i;
	int			j;

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
	int			i;
	int			j;

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

