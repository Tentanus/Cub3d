/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli  <mweverli@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 17:36:09 by mweverli      #+#    #+#                 */
/*   Updated: 2024/01/10 17:37:09 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "MLX42.h"
#include "libft.h"

static int	validateinput(int argc, char **argv)
{
	int		fd;
	size_t	filename_length;

	if (argc != 2)
		return (cbd_error(ERR_ARGUMENT), -1);
	filename_length = ft_strlen(argv[1]);
	if (filename_length <= 4
		|| ft_strncmp(&argv[1][filename_length - 4], ".cub", 5))
		return (cbd_error(ERR_ARGUMENT), -1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (cbd_error(ERR_FILE), -1);
	return (fd);
}

static void exit_hook(void *param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE) == true)
		mlx_close_window(mlx);
}

static void draw_size_square(mlx_image_t *image, int32_t x, int32_t y, size_t size)
{
	uint32_t col = 0xFF000000 | rand();

	for (size_t i = 0; i < size ; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			mlx_put_pixel(image, x + i, y + j, col);
		}
	}
}

static void draw_hook(void *param)
{
	t_cub3d *info = param;
	mlx_t *mlx = info->mlx;

	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		info->draw_y -= 2;
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		info->draw_y += 2;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		info->draw_x += 2;
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		info->draw_x -= 2;

	if (!mlx_is_key_down(mlx, MLX_KEY_SPACE))
		return ;
	else
		draw_size_square(info->image, info->draw_x, info->draw_y, 10);
}

static void info_hook(void* param)
{
	const mlx_t* mlx = param;

	ft_printf("fps: %d\n", (int) 1 / mlx->delta_time);
}

int	main(int argc, char *argv[])
{
	t_cub3d	info;

	if (parser(validateinput(argc, argv), &info) == FAILURE)
		return (FAILURE);

	info.draw_x = 10;
	info.draw_y = 10;
	mlx_image_to_window(info.mlx, info.image, 10, 10);
	mlx_loop_hook(info.mlx, info_hook, (void *) info.mlx);
	mlx_loop_hook(info.mlx, exit_hook, (void *) info.mlx);
	mlx_loop_hook(info.mlx, draw_hook, (void *) &info);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);
	return (SUCCESS);
}
