/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld  <abarteld@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 17:36:09 by abarteld      #+#    #+#                 */
/*   Updated: 2024/03/10 17:37:09 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "MLX42.h"
#include "libft.h"


static bool	load_raycaster_struct(t_cub3d *info)
{
	info->raycaster = ft_calloc(1, sizeof(t_raycaster));
	if (info->raycaster == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	info->raycaster->col_ce = info->param->col_ce;
	info->raycaster->col_fl = info->param->col_fl;
	info->raycaster->player_pos.x = info->chart->px;
	info->raycaster->player_pos.y = info->chart->py;
	if (load_textures(info->raycaster, *info->param) == FAILURE)
		return (FAILURE);
	info->raycaster->map = copy_array(info->chart->map);
	//gotta load in player direction
	// free_param(info->param);
	// free_chart(info->chart);
	return (SUCCESS);
	//other shit we need rn?
}

// static?
void	cub3d_hooks(mlx_key_data_t keydata, void *param)
{
	t_raycaster	*raycaster;

	raycaster = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(raycaster->mlx);
		return ;
	}
}

// bool	draw_ceiling(const t_raycaster raycaster)
// {
// 	while
// 	mlx_put_pixel()
// }

bool	raycaster(t_cub3d *info)
{
	if (load_raycaster_struct(info) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	if (get_mlx(info->raycaster) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	if (get_image(info->raycaster) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	// if (draw_ceiling(*info->raycaster) == FAILURE)
	// 	return (cbd_free_info(info), FAILURE);
	// if (draw_floor(*info->raycaster) == FAILURE)
	// 	return (cbd_free_info(info), FAILURE);
	mlx_key_hook(info->raycaster->mlx, &cub3d_hooks, info->raycaster);
	mlx_loop_hook(info->raycaster->mlx, &minimap_hook, info);
	mlx_loop(info->raycaster->mlx);
	return (SUCCESS);
}

// mlx_image_to_window(info->raycaster->mlx, mlx_texture_to_image(info->raycaster->mlx, info->raycaster->textures[NORTH]), 0, 0);
