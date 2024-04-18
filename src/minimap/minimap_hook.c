/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_hook.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:36:03 by mweverli      #+#    #+#                 */
/*   Updated: 2024/02/20 15:36:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "CBDminimap.h"

uint32_t	decide_colour(char c)
{
	if (c == '1')
		return (0x754400FF);
	else if (c == '0' || ft_strchr("NSWE", c))
		return (0x05FF00FF);
	else
		return (0x00000000);
}

void	fill_tile(t_minimap *mini, char **map)
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
			if (!ft_isspace(map[y][x]))
			{
				tile_to_window(mini, (tile * x) + (tile >> 1), \
					(tile * y) + (tile >> 1), 0x000000FF);
				b_tile_to_window(mini, (tile * x) + (tile >> 1), \
					(tile * y) + (tile >> 1), decide_colour(map[y][x]));
			}
			x++;
		}
		y++;
	}
}

void	minimap_hook(void *param)
{
	const t_cub3d	*info = ((t_cub3d *) param);
	t_minimap		*map;

	if (info->minimap->minimap->enabled == false)
		return ;
	map = info->minimap;
	fill_tile(map, info->raycaster->map);
	fill_player(map, info->raycaster);
}
