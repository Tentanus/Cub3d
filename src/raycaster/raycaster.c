/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli  <mweverli@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 17:36:09 by mweverli      #+#    #+#                 */
/*   Updated: 2024/03/10 17:37:09 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "MLX42.h"
#include "libft.h"


static bool	load_raycaster_struct(t_cub3d *info)
{
	info->ray = ft_calloc(1, sizeof(t_raycast));
	if (info->ray == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	info->ray->col_ce = info->par->col_ce;
	info->ray->col_fl = info->par->col_fl;
	info->ray->px = info->chart->px;
	info->ray->py = info->chart->py;
	//other shit we need rn?
	return (SUCCESS);
}

void	cub3d_hooks(mlx_key_data_t keydata, void *param)
{
	t_raycast	*ray;

	ray = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(ray->mlx);
		return ;
	}
}

bool	raycaster(t_cub3d *info)
{
	if (load_raycaster_struct(info) == FAILURE)
		return (FAILURE);
	if (get_mlx(info))
		return (cbd_free_info(info), FAILURE);
	mlx_key_hook(info->ray->mlx, &cub3d_hooks, info->ray);
	mlx_loop_hook(info->ray->mlx, &minimap_hook, info);
	mlx_loop(info->ray->mlx);
	return (SUCCESS);
}
