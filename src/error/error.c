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
#include "libft.h"

static const char *g_err_msg[_SIZE_ERRNUM + 1] = {
	[SUCCESS]	   = "-",
	[ERR_ARGUMENT] = "usage: ./Cub3d <filename>.cub",
	[ERR_FILE]	   = "unable to open file",
	[ERR_READ]	   = "unable to read file",
	[ERR_MEMORY]   = "unable to allocate memory",
	[ERR_PARSE_ID] = "unknown identifier in file [NO, SO, WE, EA, C, F]",
	[_SIZE_ERRNUM] = "END ERROR MESSAGES"};

void cbd_error(t_errnum errnum)
{
	if (errnum == SUCCESS)
		return;
	ft_putstr_fd("Cub3d: ", STDERR_FILENO);
	ft_putendl_fd(g_err_msg[errnum], STDERR_FILENO);
}
