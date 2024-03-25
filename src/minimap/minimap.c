/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:36:03 by mweverli      #+#    #+#                 */
/*   Updated: 2024/02/20 15:36:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "CBDparser.h"
#include "Cub3d.h"
#include "CBDraycaster.h"
#include "MLX42.h"
#include "libft.h"

void	fill_background(mlx_image_t *minimap)
{
	size_t	x;
	size_t	y;

	x = 0;
//	ft_memset(minimap, 0x000000FF, sizeof(*minimap));
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

void	tile_to_window(t_minimap *mini, size_t x, size_t y, uint32_t col)
{
	const uint32_t	tile = mini->tile_size;
	size_t			i;
	size_t			j;

	i = MINIMAP_BORDER;
	while (i < tile - MINIMAP_BORDER)
	{
		j = MINIMAP_BORDER;
		while (j < tile - MINIMAP_BORDER)
		{
			mlx_put_pixel(mini->minimap, (x * tile) + i, (y * tile) + j, col);
			j++;
		}
		i++;
	}
}

void	fill_tile(t_minimap *mini, char **map)
{
	uint32_t	col;
	size_t		x;
	size_t		y;

	y = 0;
//	printf("LOOP:\n");
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
//			printf("%zu\t%zu\t%c\n", x, y, map[y][x]);
			if (map[y][x] == '1')
				col = 0x754400FF; // BROWN
			else if (map[y][x] == '0' || ft_strchr("NSWE", map[y][x]))
				col = 0x05FF00FF; // GREEN
			else
				col = 0x666666FF; // GRAY
			tile_to_window(mini, x, y, col); // could remove tilesize
			x++;
		}
		y++;
	}
}

void	fill_player(t_minimap *mini, t_raycaster *raycaster)
{
	// 	Remove the 0.5
	const uint32_t	tile = mini->tile_size;
	const double	mini_pos_x = ((raycaster->player_pos.x + 0.5) * tile) \
		- (mini->player_size >> 1);
	const double	mini_pos_y = ((raycaster->player_pos.y + 0.5) * tile) \
		- (mini->player_size >> 1);
	size_t			i;
	size_t			j;

	i = 0;
	while (i < mini->player_size)
	{
		j = 0;
		while (j < mini->player_size)
		{
			mlx_put_pixel(mini->minimap, mini_pos_x + i, mini_pos_y + j, \
				0xFF0000FF);
			j++;
		}
		i++;
	}
}

void	minimap_hook(void *param)
{
	const t_cub3d	*info = ((t_cub3d *) param);
	t_minimap		*map;

	map = info->minimap;
	fill_background(map->minimap);
	fill_tile(map, info->raycaster->map);
	fill_player(map, info->raycaster);
	mlx_image_to_window(info->raycaster->mlx, map->minimap, 0, 0);
}
