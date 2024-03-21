/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:36:03 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/20 15:36:05 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CBDerror.h"
#include "Cub3d.h"
#include "MLX42.h"

bool	get_mlx(t_cub3d *info)
{
	t_raycast	*ray;

	ray = info->ray;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ray->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	if (!ray->mlx)
		return (cbd_mlx_error(), FAILURE);
	ray->screen = mlx_new_image(ray->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!ray->screen)
		return (cbd_mlx_error(), mlx_terminate(ray->mlx), FAILURE);
	ray->minimap = mlx_new_image(ray->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!ray->minimap)
		return (cbd_mlx_error(), mlx_delete_image(ray->mlx, ray->screen), \
			mlx_terminate(ray->mlx), FAILURE);
	return (SUCCESS);
}
