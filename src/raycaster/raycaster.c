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
	
	info->minimap->minimap = mlx_new_image(info->raycaster->mlx, \
		(chart->max_x + 1) * info->minimap->tile_size, \
		(chart->max_y + 1) * info->minimap->tile_size);
	if (!info->minimap->minimap)
		return (cbd_mlx_error(), mlx_terminate(info->raycaster->mlx), FAILURE);
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
    //strafe left (currently inverted)
	if ((keydata.key == MLX_KEY_A) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
    {
		double	rotspeed = M_PI_2;
		double	tempDirX = raycaster->player_dir.x;
		double	tempDirY = raycaster->player_dir.y;

		tempDirX = raycaster->player_dir.x * cos(-rotspeed) - raycaster->player_dir.y * sin(-rotspeed);
		tempDirY = raycaster->player_dir.x * sin(-rotspeed) + tempDirY * cos(-rotspeed);
		if(raycaster->map[(int)raycaster->player_pos.y][(int)(raycaster->player_pos.x + tempDirX * raycaster->move_speed)] != '1')
			raycaster->player_pos.x += tempDirX * raycaster->move_speed;
		if(raycaster->map[(int)(raycaster->player_pos.y + tempDirY * raycaster->move_speed)][(int)raycaster->player_pos.x] != '1')
			raycaster->player_pos.y += tempDirY * raycaster->move_speed;
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
	//strafe right (currently inverted)
	if ((keydata.key == MLX_KEY_D) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		double	rotspeed = M_PI_2;
		double	tempDirX = raycaster->player_dir.x;
		double	tempDirY = raycaster->player_dir.y;

		tempDirX = raycaster->player_dir.x * cos(rotspeed) - raycaster->player_dir.y * sin(rotspeed);
		tempDirY = raycaster->player_dir.x * sin(rotspeed) + tempDirY * cos(rotspeed);
		if(raycaster->map[(int)raycaster->player_pos.y][(int)(raycaster->player_pos.x + tempDirX * raycaster->move_speed)] != '1')
			raycaster->player_pos.x += tempDirX * raycaster->move_speed;
		if(raycaster->map[(int)(raycaster->player_pos.y + tempDirY * raycaster->move_speed)][(int)raycaster->player_pos.x] != '1')
			raycaster->player_pos.y += tempDirY * raycaster->move_speed;
	}
	//Rotate To right
	if ((keydata.key == MLX_KEY_Q) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		double  oldDirX = raycaster->player_dir.x;
		raycaster->player_dir.x = oldDirX * cos(-0.0698131) - raycaster->player_dir.y * sin(-0.0698131);
		raycaster->player_dir.y = oldDirX * sin(-0.0698131) + raycaster->player_dir.y * cos(-0.0698131);
		double  oldplaneX = raycaster->plane.x;
		raycaster->plane.x = oldplaneX * cos(-0.0698131) - raycaster->plane.y * sin(-0.0698131);
		raycaster->plane.y = oldplaneX * sin(-0.0698131) + raycaster->plane.y * cos(-0.0698131);
	}
	//Rotate To left
	if ((keydata.key == MLX_KEY_E) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		double  oldDirX = raycaster->player_dir.x;
		raycaster->player_dir.x = oldDirX * cos(0.0698131) - raycaster->player_dir.y * sin(0.0698131);
		raycaster->player_dir.y = oldDirX * sin(0.0698131) + raycaster->player_dir.y * cos(0.0698131);
		double  oldplaneX = raycaster->plane.x;
		raycaster->plane.x = oldplaneX * cos(0.0698131) - raycaster->plane.y * sin(0.0698131);
		raycaster->plane.y = oldplaneX * sin(0.0698131) + raycaster->plane.y * cos(0.0698131);
	}
}
/*
{
double oldDirX = dirX;
dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
double oldPlaneX = planeX;
planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}
*/
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
	mlx_key_hook(info->raycaster->mlx, &cub3d_key_hook, info->raycaster);	//translate turning and moving
	
	if (load_minimap_struct(info) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	mlx_loop_hook(info->raycaster->mlx, &minimap_hook, info);
	mlx_loop(info->raycaster->mlx);
	return (SUCCESS);
}

// mlx_image_to_window(info->raycaster->mlx, mlx_texture_to_image(info->raycaster->mlx, info->raycaster->textures[NORTH]), 0, 0);
	// if (draw_ceiling(*info->raycaster) == FAILURE)
	// 	return (cbd_free_info(info), FAILURE);
	// if (draw_floor(*info->raycaster) == FAILURE)
	// 	return (cbd_free_info(info), FAILURE);
