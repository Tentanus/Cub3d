/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli  <mweverli@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 17:36:09 by mweverli      #+#    #+#                 */
/*   Updated: 2024/01/10 17:37:09 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "CBDerror.h"
#include "MLX42.h"
#include "libft.h"

static const char	*g_err_msg[ERR_SIZE + 1] = {
[ERR_SUCCESS] = "-",
[ERR_ARGUMENT] = "usage: ./Cub3d [filename].cub",
[ERR_FILE] = "unable to open file",
[ERR_READ] = "unable to read file",
[ERR_MEMORY] = "unable to allocate memory",
[ERR_PARSE_ID] = "unknown identifier in file [NO, SO, WE, EA, C, F]",
[ERR_PARSE_FORMAT] = "unable to parse due to unknown format in file",
[ERR_PARSE_RGB] = "unable to parse colour value [0 - 255]",
[ERR_PARSE_TRAIL] = "unable to parse due to line with trailing characters",
[ERR_PARSE_FILLED] = "unable to parse due to multiple similar identifier",
[ERR_MAP_ENCLOSED] = "map is not enclosed by walls [1]",
[ERR_SIZE] = "END ERROR MESSAGES"};

void	cbd_error(t_errnum errnum)
{
	if (errnum == ERR_SUCCESS)
		return ;
	ft_putstr_fd("ERROR\n", STDERR_FILENO);
	ft_putendl_fd(g_err_msg[errnum], STDERR_FILENO);
}

void	cbd_mlx_error(void)
{
	ft_putstr_fd("cub3D: ", STDERR_FILENO);
	ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
}
