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

int	main(int argc, char *argv[])
{
// All errors must be formatted as Error\n + explicit error message
	t_cub3d	info;

	if (parser(validateinput(argc, argv), &info) == FAILURE)
		return (FAILURE);
	if (raycaster(&info) == FAILURE)
		return (FAILURE);
	mlx_terminate(info.raycaster->mlx);
	cbd_free_info(&info);
	return (SUCCESS);
}
