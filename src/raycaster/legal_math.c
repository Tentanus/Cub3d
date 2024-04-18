/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarteld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:06:48 by abarteld          #+#    #+#             */
/*   Updated: 2024/03/21 14:06:49 by abarteld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "CBDraycaster.h"
#include "MLX42.h"
#include "libft.h"

t_ray	ray_init(const t_raycaster raycaster, const int x)
{
	t_ray	ray;

	ray.camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray.pos.x = raycaster.player_pos.x;
	ray.pos.y = raycaster.player_pos.y;
	ray.dir.x = raycaster.player_dir.x + raycaster.plane.x * ray.camera_x;
	ray.dir.y = raycaster.player_dir.y + raycaster.plane.y * ray.camera_x;
	ray.map_x = (int)raycaster.player_pos.x;
	ray.map_y = (int)raycaster.player_pos.y;
	ray.delta_dist.x = 1e30;
	if (ray.dir.x != 0)
		ray.delta_dist.x = fabs(1 / ray.dir.x);
	ray.delta_dist.y = 1e30;
	if (ray.dir.y != 0)
		ray.delta_dist.y = fabs(1 / ray.dir.y);
	return (ray);
}

t_ray	ray_side_dist(t_ray ray)
{
	if (ray.dir.x < 0)
	{
		ray.step.x = -1;
		ray.side_dist.x = (ray.pos.x - ray.map_x) * ray.delta_dist.x;
	}
	else
	{
		ray.step.x = 1;
		ray.side_dist.x = (ray.map_x + 1.0 - ray.pos.x) * ray.delta_dist.x;
	}
	if (ray.dir.y < 0)
	{
		ray.step.y = -1;
		ray.side_dist.y = (ray.pos.y - ray.map_y) * ray.delta_dist.y;
	}
	else
	{
		ray.step.y = 1;
		ray.side_dist.y = (ray.map_y + 1.0 - ray.pos.y) * ray.delta_dist.y;
	}
	return (ray);
}

t_ray	ray_dda(t_ray ray, char **map)
{
	while (1)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map_x += ray.step.x;
			ray.side = 0;
			ray.wall_dir = WEST;
			if (ray.step.x > 0)
				ray.wall_dir = EAST;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map_y += ray.step.y;
			ray.side = 1;
			ray.wall_dir = NORTH;
			if (ray.step.y > 0)
				ray.wall_dir = SOUTH;
		}
		if (map[ray.map_y][ray.map_x] == '1')
			break ;
	}
	return (ray);
}

t_ray	ray_draw_colours(t_ray ray, const int x, const t_raycaster raycaster)
{
	int	y;

	ray.line_height = (int)(WINDOW_HEIGHT / ray.perp_dist);
	ray.draw_start = -ray.line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray.draw_start < 0)
		ray.draw_start = 0;
	ray.draw_end = ray.line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray.draw_end >= WINDOW_HEIGHT)
		ray.draw_end = WINDOW_HEIGHT - 1;
	y = 0;
	while (y < ray.draw_start)
	{
		mlx_put_pixel(raycaster.screen, x, y, raycaster.col_ce);
		y++;
	}
	y = WINDOW_HEIGHT - 1;
	while (y > ray.draw_end)
	{
		mlx_put_pixel(raycaster.screen, x, y, raycaster.col_fl);
		y--;
	}
	return (ray);
}

void	cub3d_math_hook(void *param)
{
	t_raycaster	*raycaster;
	t_ray		ray;
	int			x;

	raycaster = param;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray = ray_init(*raycaster, x);
		ray = ray_side_dist(ray);
		ray = ray_dda(ray, raycaster->map);
		if (ray.side == 0)
			ray.perp_dist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perp_dist = (ray.side_dist.y - ray.delta_dist.y);
		ray = ray_draw_colours(ray, x, *raycaster);
		ray_texture_calc(ray, x, *raycaster);
		x++;
	}
}
