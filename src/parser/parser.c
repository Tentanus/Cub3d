/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:30:46 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/13 19:30:49 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"
#include "libft.h"

// read the info file
// load the elements into the struct (fail if an element is either missing or misformatted)
// check the path

// mlx
// read the texture files given (fail if a texture cannot be read) move to later?

static char	*read_fd(int fd)
{
	char	*line;
	char	*tmp;

	line = ft_calloc(READ_CHUNK, sizeof(char));
	if (read(fd, line, READ_CHUNK) != READ_CHUNK)
	{
		close(fd);
		return (line);
	}
	tmp = ft_calloc(READ_CHUNK, sizeof(char));
	while (read(fd, tmp, READ_CHUNK) == READ_CHUNK)
	{
		line = ft_strjoin_fs1(line, tmp);
	}
	close(fd);
	free(tmp);
	return (line);
}

// this is a temporary fucntion; could set it up so it checks
// if all values have been filled after get_data & get_map
/*
static bool	set_default(t_cub3d *info)
{
	if (!info->text_no)
		info->text_no = ft_strdup(DEF_TEXT_NO);
	if (!info->text_so)
		info->text_so = ft_strdup(DEF_TEXT_SO);
	if (!info->text_we)
		info->text_we = ft_strdup(DEF_TEXT_WE);
	if (!info->text_ea)
		info->text_ea = ft_strdup(DEF_TEXT_EA);
	if (!info->col_fl)
		info->col_fl = DEF_COL_FL;
	if (!info->col_ce)
		info->col_ce = DEF_COL_CE;
	if (!info->text_no || !info->text_so || !info->text_we || !info->text_ea
		|| !info->col_fl || !info->col_ce)
		return (FAILURE);
	return (SUCCESS);
}
*/

int	parser(int fd, t_cub3d *info)
{
	char	*fileline;
	ssize_t	idx;

	if (fd == -1)
		return (FAILURE);
	fileline = read_fd(fd);
	if (fileline == NULL)
		return (cbd_error(ERR_MEMORY), FAILURE);
	ft_bzero(info, sizeof(t_cub3d));
	idx = 0;
	if (get_data(info, fileline, &idx))
		return (cbd_free_info(info), FAILURE);
	if (get_map(info, fileline, &idx))
		return (cbd_free_info(info), FAILURE);
	free(fileline);
	if (parse_map(info->chart) == FAILURE)
		return (print_info(info), cbd_free_info(info), FAILURE);
// set_default(info);
	if (check_path(info->chart) == FAILURE)
		return (print_info(info), cbd_free_info(info), FAILURE);
	if (get_mlx(info))
		return (cbd_free_info(info), FAILURE);
	print_info(info);	// TODO: remove PRINT
	return (SUCCESS);
}
