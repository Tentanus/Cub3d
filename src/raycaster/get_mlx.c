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

#include "Cub3d.h"

bool	get_mlx(t_cub3d *info)
{
	t_raycast	*ray;
	size_t		size_mm;

	ray = info->ray;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ray->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	if (!ray->mlx)
		return (cbd_mlx_error(), FAILURE);
	ray->screen = mlx_new_image(ray->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!ray->screen)
		return (cbd_mlx_error(), mlx_terminate(ray->mlx), FAILURE);
	size_mm = \
		((WINDOW_WIDTH >> MINIMAP_SIZE) + (WINDOW_HEIGHT >> MINIMAP_SIZE)) >> 1;
		// MINIMAP_SIZE DEFAULT SHOULD BE SET TO 3
	ray->minimap = mlx_new_image(ray->mlx, size_mm, size_mm);
	if (!ray->minimap)
		return (cbd_mlx_error(), mlx_delete_image(ray->mlx, ray->screen), \
			mlx_terminate(ray->mlx), FAILURE);
	return (SUCCESS);
}
