/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld  <abarteld@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 17:36:09 by abarteld      #+#    #+#                 */
/*   Updated: 2024/03/10 17:37:09 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "CBDminimap.h"

void	rotation_key_hook(mlx_key_data_t keydata, t_raycaster *raycaster)
{
	const double	x_dir_old = raycaster->player_dir.x;
	const double	x_plane_old = raycaster->plane.x;
	double			rotation;

	if ((keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_LEFT) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotation = -0.078539816;
	else if ((keydata.key == MLX_KEY_E || keydata.key == MLX_KEY_RIGHT) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotation = 0.078539816;
	if ((keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_LEFT) || \
		(keydata.key == MLX_KEY_E || keydata.key == MLX_KEY_RIGHT))
	{
		raycaster->player_dir.x = x_dir_old * cos(rotation) - \
			raycaster->player_dir.y * sin(rotation);
		raycaster->player_dir.y = x_dir_old * sin(rotation) + \
			raycaster->player_dir.y * cos(rotation);
		raycaster->plane.x = x_plane_old * cos(rotation) - \
			raycaster->plane.y * sin(rotation);
		raycaster->plane.y = x_plane_old * sin(rotation) + \
			raycaster->plane.y * cos(rotation);
	}
}

static void	check_walls(double x, double y, t_raycaster *raycaster)
{
	if (raycaster->map[(int)raycaster->player_pos.y] \
		[(int)(raycaster->player_pos.x + x * raycaster->move_speed)] != '1')
		raycaster->player_pos.x += x * raycaster->move_speed;
	if (raycaster->map[(int)(raycaster->player_pos.y + y * \
		raycaster->move_speed)][(int)raycaster->player_pos.x] != '1')
		raycaster->player_pos.y += y * raycaster->move_speed;
}

void	move_sideway_key_hook(mlx_key_data_t keydata, t_raycaster *raycaster)
{
	double		rotspeed;
	double		x_dir_tmp;
	double		y_dir_tmp;

	x_dir_tmp = raycaster->player_dir.x;
	y_dir_tmp = raycaster->player_dir.y;
	if ((keydata.key == MLX_KEY_A) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotspeed = -M_PI_2;
	if ((keydata.key == MLX_KEY_D) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotspeed = M_PI_2;
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		x_dir_tmp = raycaster->player_dir.x * cos(rotspeed) - \
			y_dir_tmp * sin(rotspeed);
		y_dir_tmp = raycaster->player_dir.x * sin(rotspeed) + \
			y_dir_tmp * cos(rotspeed);
		check_walls(x_dir_tmp, y_dir_tmp, raycaster);
	}
}

void	move_forward_key_hook(mlx_key_data_t keydata, t_raycaster *rct)
{
	if ((keydata.key == MLX_KEY_W) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (rct->map[(int)rct->player_pos.y][(int)(rct->player_pos.x + \
			rct->player_dir.x * rct->move_speed)] != '1')
			rct->player_pos.x += rct->player_dir.x * rct->move_speed;
		if (rct->map[(int)(rct->player_pos.y + rct->player_dir.y * \
			rct->move_speed)][(int)rct->player_pos.x] != '1')
			rct->player_pos.y += rct->player_dir.y * rct->move_speed;
	}
	if ((keydata.key == MLX_KEY_S) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (rct->map[(int)rct->player_pos.y][(int)(rct->player_pos.x - \
			rct->player_dir.x * rct->move_speed)] != '1')
			rct->player_pos.x -= rct->player_dir.x * rct->move_speed;
		if (rct->map[(int)(rct->player_pos.y - rct->player_dir.y * \
			rct->move_speed)][(int)rct->player_pos.x] != '1')
			rct->player_pos.y -= rct->player_dir.y * rct->move_speed;
	}
}

void	cub3d_key_hook(mlx_key_data_t keydata, void *param)
{
	t_raycaster	*raycaster;

	raycaster = ((t_cub3d *) param)->raycaster;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(raycaster->mlx);
		return ;
	}
	minimap_key_hook(keydata, ((t_cub3d *)param)->minimap);
	rotation_key_hook(keydata, raycaster);
	move_sideway_key_hook(keydata, raycaster);
	move_forward_key_hook(keydata, raycaster);
}
