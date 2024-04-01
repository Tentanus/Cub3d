/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_hoor.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:36:03 by mweverli      #+#    #+#                 */
/*   Updated: 2024/02/20 15:36:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "CBDminimap.h"

/*
void	fill_background(mlx_image_t *minimap)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < minimap->width)
	{
		y = 0;
		while (y < minimap->height)
		{
			mlx_put_pixel(minimap, x, y, 0x000000FF);
			y++;
		}
		x++;
	}
}
//	*/

void	fill_background(t_minimap *mini, char **map)
{
	const uint32_t	tile = mini->tile_size;
	size_t			x;
	size_t			y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (ft_isdigit(map[y][x]) || ft_strchr("NSWE", map[y][x]))
				tile_to_window(mini, (tile * x) + (tile >> 1), \
					(tile * y) + (tile >> 1), 0x000000FF);
			x++;
		}
		y++;
	}
}

void	fill_tile(t_minimap *mini, char **map)
{
	const uint32_t	tile = mini->tile_size;
	uint32_t		col;
	size_t			x;
	size_t			y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '1')
				col = 0x754400FF; // BROWN
			else if (map[y][x] == '0' || ft_strchr("NSWE", map[y][x]))
				col = 0x05FF00FF; // GREEN
			else
			{
				x++;
				continue;
			}
			b_tile_to_window(mini, (tile * x) + (tile >> 1), \
					(tile * y) + (tile >> 1), col);
			x++;
		}
		y++;
	}
}

void	minimap_hook(void *param)
{
	const t_cub3d	*info = ((t_cub3d *) param);
	t_minimap		*map;

	map = info->minimap;
//	fill_background(map->minimap);
	fill_background(map, info->raycaster->map);
	fill_tile(map, info->raycaster->map);
	fill_player(map, info->raycaster);
	mlx_image_to_window(info->raycaster->mlx, map->minimap, 0, 0); //TODO: this can be done before loop is started
}
