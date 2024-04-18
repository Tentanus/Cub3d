/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarteld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:30:23 by abarteld          #+#    #+#             */
/*   Updated: 2024/04/10 19:30:24 by abarteld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "MLX42.h"
#include "libft.h"

static u_int32_t	get_colour_from_pixel(u_int8_t *pixel)
{
	return ((u_int32_t)pixel[0] << 24 | (u_int32_t)pixel[1] << 16 | \
		(u_int32_t)pixel[2] << 8 | (u_int32_t)pixel[3]);
}

static void	ray_texture_draw(t_ray ray,	\
		t_texture_info tex_info, const int x, const t_raycaster raycaster)
{
	uint32_t		colour;
	int				y;

	y = ray.draw_start;
	while (y <= ray.draw_end)
	{
		tex_info.texture_y = (int)tex_info.texture_pos & \
			(raycaster.textures[ray.wall_dir]->height - 1);
		tex_info.texture_pos += tex_info.step;
		tex_info.pixel_index = (raycaster.textures[ray.wall_dir]->height * \
			tex_info.texture_y + tex_info.texture_x) * \
			raycaster.textures[ray.wall_dir]->bytes_per_pixel;
		colour = get_colour_from_pixel(\
		&raycaster.textures[ray.wall_dir]->pixels[tex_info.pixel_index]);
		mlx_put_pixel(raycaster.screen, x, y, colour);
		y++;
	}
}

void	ray_texture_calc(t_ray ray, const int x, const t_raycaster raycaster)
{
	t_texture_info	tex_info;

	if (ray.side == 0)
		tex_info.wall_x = ray.pos.y + ray.perp_dist * ray.dir.y;
	else
		tex_info.wall_x = ray.pos.x + ray.perp_dist * ray.dir.x;
	tex_info.wall_x = -tex_info.wall_x + floor(tex_info.wall_x) + 1;
	tex_info.texture_x = \
	(int)(tex_info.wall_x * (double)raycaster.textures[ray.wall_dir]->width);
	if (ray.side == 0 && ray.dir.x > 0)
		tex_info.texture_x = \
		raycaster.textures[ray.wall_dir]->width - tex_info.texture_x - 1;
	else if (ray.side == 1 && ray.dir.y < 0)
		tex_info.texture_x = \
		raycaster.textures[ray.wall_dir]->width - tex_info.texture_x - 1;
	tex_info.step = \
	1.0 * raycaster.textures[ray.wall_dir]->height / ray.line_height;
	tex_info.texture_pos = (ray.draw_start - (WINDOW_HEIGHT >> 1) + \
		(ray.line_height >> 1)) * tex_info.step;
	ray_texture_draw(ray, tex_info, x, raycaster);
}
