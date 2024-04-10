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

static void	load_player_direction(t_raycaster *raycaster, char player_dir)
{
	if (player_dir == 'N' || player_dir == 'S')
	{
		raycaster->player_dir.x = 0.0;
		raycaster->player_dir.y = -1.0;
		if (player_dir == 'S')
			raycaster->player_dir.y = 1.0;
		raycaster->plane.x = 0.66;
		if (player_dir == 'S')
			raycaster->plane.x = -0.66;
		raycaster->plane.y = 0.0;
	}
	else if (player_dir == 'E' || player_dir == 'W')
	{
		raycaster->player_dir.x = 1.0;
		if (player_dir == 'W')
			raycaster->player_dir.x = -1.0;
		raycaster->player_dir.y = 0.0;
		raycaster->plane.x = 0.00;
		raycaster->plane.y = 0.66;
		if (player_dir == 'W')
			raycaster->plane.y = -0.66;
	}
}

static bool	load_raycaster_struct(t_cub3d *info)
{
	info->raycaster = ft_calloc(1, sizeof(t_raycaster));
	if (info->raycaster == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	info->raycaster->col_ce = info->param->col_ce;
	info->raycaster->col_fl = info->param->col_fl;
	if (load_textures(info->raycaster, *info->param) == FAILURE)
		return (FAILURE);
	// free_param(info->param); //and set to NULL to avoid double free
	info->raycaster->player_pos.x = info->chart->px + 0.5;
	info->raycaster->player_pos.y = info->chart->py + 0.5;
	load_player_direction(info->raycaster, info->chart->player_direction);
	info->raycaster->move_speed = 0.117;
	info->raycaster->map = copy_array(info->chart->map);
	if (!info->raycaster->map)
		return (FAILURE);
	// free_chart(info->chart); //and set to NULL to avoid double free
	return (SUCCESS);
}

static bool	load_minimap_struct(t_cub3d *info)
{
	const t_map		*chart = info->chart;
	const size_t	size_mm = \
		((WINDOW_WIDTH >> MINIMAP_SIZE_MOD) + \
		(WINDOW_HEIGHT >> MINIMAP_SIZE_MOD)) >> 1;

	info->minimap = ft_calloc(1, sizeof(t_minimap));
	if (info->minimap == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	info->minimap->dimention_x = chart->max_x;
	info->minimap->dimention_y = chart->max_y;
	info->minimap->tile_size = size_mm / \
		(ft_ternary(\
			chart->max_x > chart->max_y, chart->max_x, chart->max_y) + 1);
	if (info->minimap->tile_size % 2 == 0)
		info->minimap->tile_size += 1;
	info->minimap->player_size = info->minimap->tile_size >> 2;
	info->minimap->minimap = mlx_new_image(info->raycaster->mlx, \
		(chart->max_x + 1) * info->minimap->tile_size, \
		(chart->max_y + 1) * info->minimap->tile_size);
	if (!info->minimap->minimap)
		return (cbd_mlx_error(), mlx_terminate(info->raycaster->mlx), FAILURE);
	return (SUCCESS);
}

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
	mlx_loop_hook(info->raycaster->mlx, &minimap_hook, info);
	mlx_loop_hook(info->raycaster->mlx, &cub3d_math_hook, info->raycaster);
	mlx_key_hook(info->raycaster->mlx, &cub3d_key_hook, info);
	mlx_loop(info->raycaster->mlx);
	return (SUCCESS);
}
