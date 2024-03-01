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

bool get_mlx(t_cub3d *info)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	info->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	if (!info->mlx)
		return (cbd_mlx_error(), FAILURE);
	info->image = mlx_new_image(info->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!info->image)
		return (cbd_mlx_error(), mlx_terminate(info->mlx), FAILURE);
		
	return (SUCCESS);
}
