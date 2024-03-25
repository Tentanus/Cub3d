/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_mlx.c                                          :+:    :+:            */
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

void fill_background(mlx_image_t *minimap)
{
//	ft_memset(minimap, 0x000000FF, sizeof(*minimap));
	for (size_t x = 0 ; x < minimap->width ; x++)
	{
		for (size_t y = 0 ; y < minimap->height ; y++)
		{
			mlx_put_pixel(minimap, x, y, 0x000000FF);
		}
	}
}

void tile_to_window(t_minimap *mini, size_t x, size_t y, uint32_t col)
{
	const uint32_t tile = mini->tile_size;

	for (size_t i = 1; i < tile ; i++)
	{
		for (size_t j = 1; j < tile ; j++)
		{
			mlx_put_pixel(mini->minimap, (x * tile) + i , (y * tile) + j, col);
		}
	}

}

void fill_tile(t_minimap *mini, char **map)
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
			if (map[y][x] ==  '1')
				col = 0x754400FF; // BROWN
			else if (map[y][x] ==  '0' || ft_strchr("NSWE", map[y][x]))
				col = 0x05FF00FF; // GREEN
			else
				col = 0x666666FF; // GRAY
			tile_to_window(mini, x, y, col); // could remove tilesize
			x++;
		}
		y++;
	}
}

void fill_player(t_minimap *mini, t_raycaster *raycaster)
{
	const uint32_t tile = mini->tile_size;
	const uint32_t player_size = mini->player_size;
	const double mini_pos_x = ((raycaster->player_pos.x + 0.5) * tile) \
		- (player_size >> 1);
	const double mini_pos_y = ((raycaster->player_pos.y + 0.5) * tile) \
		- (player_size >> 1);

	for (size_t i = 1; i < player_size ; i++)
		for (size_t j = 1; j < player_size ; j++)
			mlx_put_pixel(mini->minimap, mini_pos_x + i, mini_pos_y + j, 0xFF0000FF);
}

void minimap_hook(void *param)
{
	const t_cub3d	*info = ((t_cub3d *) param);
	t_minimap	*map;
	
	map = info->minimap;
	fill_background(map->minimap);
	fill_tile(map, info->raycaster->map);
	fill_player(map, info->raycaster);
	mlx_image_to_window(info->raycaster->mlx, map->minimap, 0, 0);
}
