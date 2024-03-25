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
#include "MLX42.h"
#include "Cub3d.h"

void fill_background(mlx_image_t *minimap)
{
	for (size_t x = 0 ; x < minimap->width ; x++)
	{
		for (size_t y = 0 ; y < minimap->height ; y++)
		{
			mlx_put_pixel(minimap, x, y, 0x000000FF);
		}
	}
}

void minimap_hook(void *param)
{
	const t_raycast *ray = ((t_cub3d *)param)->ray;
	const size_t tile = 32;
	const size_t mapsize = ray->minimap->width;

	fill_background(ray->minimap);
	fill_map(ray->minimap,)
	(void) tile;
	mlx_image_to_window(ray->mlx, ray->minimap, 0, 0);
	(void) mapsize;
//	fill_player();
}
