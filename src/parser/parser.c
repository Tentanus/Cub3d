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

#include <unistd.h>

static char	**read_fd(int fd)
{
	char	*res;
	char	*line;

	res = ft_calloc(1, sizeof(char));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!ft_stris(line, ft_isspace))
			res = ft_strjoin_fs1(res, line);
		free(line);
		line = get_next_line(fd);
	}
#ifdef LOG
	ft_printf("-=- START LOG:\tREAD FILE -=-\n|--------------\n");
	ft_printf("%s\n\n", res);
	ft_printf("-=- END LOG:\tREAD FILE -=-\n|--------------\n", res);
#endif
	close(fd);
	return (ft_split(res, '\n'));
}

// this is a temporary fucntion; could set it up so it checks
// if all values have been filled after get_data & get_map
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

int	parser(int fd, t_cub3d *info)
{
	char	**filelines;
	ssize_t	idx;

	idx = 0;
	if (fd == -1)
		return (FAILURE);
	filelines = read_fd(fd);
	if (filelines == NULL)
		return (cbd_error(ERR_MEMORY), FAILURE);
	ft_bzero(info, sizeof(t_cub3d));
	if (get_data(info, filelines, &idx))
		return (cbd_free_info(info), FAILURE);
	if (get_map(info, filelines, &idx))
		return (cbd_free_info(info), FAILURE);
	set_default(info);
	print_info(info);
	return (SUCCESS);
}
