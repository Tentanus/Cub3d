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

// #include "CBDerror.h"
#include "Cub3d.h"
#include "MLX42.h"

bool	load_textures(t_raycaster *raycaster, const t_param param)
{
	int				i;

	raycaster->textures[NORTH] = mlx_load_png(param.text_no);
	raycaster->textures[EAST] = mlx_load_png(param.text_ea);
	raycaster->textures[SOUTH] = mlx_load_png(param.text_so);
	raycaster->textures[WEST] = mlx_load_png(param.text_we);
	i = 0;
	while (i < 4)
	{
		if (!raycaster->textures[i])
			return (cbd_error(ERR_MEMORY), FAILURE);
		i++;
	}
// mlx_delete_texture(texture);
	return (SUCCESS);
}

bool	get_image(t_raycaster *raycaster)
{
	const size_t size_mm = \
		((WINDOW_WIDTH >> MINIMAP_SIZE) + (WINDOW_HEIGHT >> MINIMAP_SIZE)) >> 1;
		// TODO: MINIMAP_SIZE DEFAULT SHOULD BE SET TO 3
	raycaster->minimap= mlx_new_image(raycaster->mlx, size_mm, size_mm);
	if (!raycaster->minimap)
		return (cbd_mlx_error(), mlx_terminate(raycaster->mlx), FAILURE);
	raycaster->screen= mlx_new_image(raycaster->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!raycaster->screen)
		return (cbd_mlx_error(), mlx_terminate(raycaster->mlx), FAILURE);
	return (SUCCESS);
}

bool	get_mlx(t_raycaster *raycaster)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	raycaster->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	if (!raycaster->mlx)
		return (cbd_mlx_error(), FAILURE);
	return (SUCCESS);
}