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

static bool load_minimap_struct(t_cub3d *info)
{
	const t_map *chart = info->chart;
	const size_t size_mm = \
		((WINDOW_WIDTH >> MINIMAP_SIZE_MOD) + \
		(WINDOW_HEIGHT >> MINIMAP_SIZE_MOD)) >> 1;
		// TODO: MINIMAP_SIZE DEFAULT SHOULD BE SET TO 3
	
	info->minimap = ft_calloc(1, sizeof(t_minimap));
	if (info->minimap == NULL)
		return (cbd_error(ERR_MEMORY), NULL);

	info->minimap->dimention_x = chart->max_x;
	info->minimap->dimention_y = chart->max_y;
		
	info->minimap->tile_size = size_mm / \
		(ft_ternary(chart->max_x > chart->max_y, chart->max_x, chart->max_y) + 1);
	if (info->minimap->tile_size % 2 == 0)
		info->minimap->tile_size += 1;
	info->minimap->player_size = info->minimap->tile_size >> 2;
	
//	info->minimap->minimap = mlx_new_image(info->raycaster->mlx, \
//										size_mm, size_mm);
	info->minimap->minimap = mlx_new_image(info->raycaster->mlx, \
		(chart->max_x + 1) * info->minimap->tile_size, \
		(chart->max_y + 1) * info->minimap->tile_size);
	if (!info->minimap->minimap)
		return (cbd_mlx_error(), mlx_terminate(info->raycaster->mlx), FAILURE);
	return (SUCCESS);
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
	if (load_minimap_struct(info) == FAILURE)
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
