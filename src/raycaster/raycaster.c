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
	info->raycaster->player_pos.x = info->chart->px + 0.5; //to centre in the square
	info->raycaster->player_pos.y = info->chart->py + 0.5; //to centre in the square
	load_player_direction(info->raycaster, info->chart->player_direction);
	info->raycaster->move_speed = 0.117; //some safety needed here
	info->raycaster->map = copy_array(info->chart->map);
	if (!info->raycaster->map)
		return (FAILURE);
	// free_chart(info->chart); //and set to NULL to avoid double free
	return (SUCCESS);
}

// static?
void	cub3d_key_hook(mlx_key_data_t keydata, void *param)
{
	t_raycaster	*raycaster;

	raycaster = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(raycaster->mlx);
		return ;
	}
	//move forward
	if ((keydata.key == MLX_KEY_W) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if(raycaster->map[(int)raycaster->player_pos.y][(int)(raycaster->player_pos.x + raycaster->player_dir.x * raycaster->move_speed)] != '1')
			raycaster->player_pos.x += raycaster->player_dir.x * raycaster->move_speed;
		if(raycaster->map[(int)(raycaster->player_pos.y + raycaster->player_dir.y * raycaster->move_speed)][(int)raycaster->player_pos.x] != '1')
			raycaster->player_pos.y += raycaster->player_dir.y * raycaster->move_speed;
    }
    //strafe left
	if ((keydata.key == MLX_KEY_A) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
    {
		if(raycaster->map[(int)(raycaster->player_pos.y - raycaster->player_dir.x * raycaster->move_speed)][(int)(raycaster->player_pos.x)] != '1')
			raycaster->player_pos.y -= raycaster->player_dir.x * raycaster->move_speed;
		if(raycaster->map[(int)(raycaster->player_pos.y)][(int)(raycaster->player_pos.x - raycaster->player_dir.y * raycaster->move_speed)] != '1')
			raycaster->player_pos.x -= raycaster->player_dir.y * raycaster->move_speed;
    }
	//move back
	if ((keydata.key == MLX_KEY_S) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if(raycaster->map[(int)raycaster->player_pos.y][(int)(raycaster->player_pos.x - raycaster->player_dir.x * raycaster->move_speed)] != '1')
			raycaster->player_pos.x -= raycaster->player_dir.x * raycaster->move_speed;
		if(raycaster->map[(int)(raycaster->player_pos.y - raycaster->player_dir.y * raycaster->move_speed)][(int)raycaster->player_pos.x] != '1')
			raycaster->player_pos.y -= raycaster->player_dir.y * raycaster->move_speed;
	}
	//strafe right
	if ((keydata.key == MLX_KEY_D) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if(raycaster->map[(int)(raycaster->player_pos.y + raycaster->player_dir.x * raycaster->move_speed)][(int)(raycaster->player_pos.x)] != '1')
			raycaster->player_pos.y += raycaster->player_dir.x * raycaster->move_speed;
		if(raycaster->map[(int)(raycaster->player_pos.y)][(int)(raycaster->player_pos.x + raycaster->player_dir.y * raycaster->move_speed)] != '1')
			raycaster->player_pos.x += raycaster->player_dir.y * raycaster->move_speed;
	}
}

// bool	draw_ceiling(const t_raycaster raycaster)
// {
// 	while
// 	mlx_put_pixel()
// }
void illegal_math(void *parameter);

bool	raycaster(t_cub3d *info)
{
	if (load_raycaster_struct(info) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	if (get_mlx(info->raycaster) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	if (get_image(info->raycaster) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	// mlx_loop_hook(info->raycaster->mlx, &cub3d_math_hook, info->raycaster);	
	mlx_loop_hook(info->raycaster->mlx, &illegal_math, info->raycaster);	
	// illegal_math(*info->raycaster);
	mlx_key_hook(info->raycaster->mlx, &cub3d_key_hook, info->raycaster);	//translate turning and moving
	mlx_loop(info->raycaster->mlx);
	return (SUCCESS);
}

// mlx_image_to_window(info->raycaster->mlx, mlx_texture_to_image(info->raycaster->mlx, info->raycaster->textures[NORTH]), 0, 0);
	// if (draw_ceiling(*info->raycaster) == FAILURE)
	// 	return (cbd_free_info(info), FAILURE);
	// if (draw_floor(*info->raycaster) == FAILURE)
	// 	return (cbd_free_info(info), FAILURE);
