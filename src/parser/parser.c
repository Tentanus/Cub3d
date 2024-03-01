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

// static char	**read_fd(int fd) //change to ditch the GNL
// {
// 	char	*res;
// 	char	*line;

// 	res = ft_calloc(1, sizeof(char));
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (!ft_stris(line, ft_isspace))
// 			res = ft_strjoin_fs1(res, line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// #ifdef LOG
// 	ft_printf("-=- START LOG:\tREAD FILE -=-\n|--------------\n");
// 	ft_printf("%s\n\n", res);
// 	ft_printf("-=- END LOG:\tREAD FILE -=-\n|--------------\n", res);
// #endif
// 	close(fd);
// 	return (ft_split(res, '\n'));
// }

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

static bool	get_mappi(t_cub3d *info, char **line, ssize_t *idx)
{
	ssize_t	i;

	info->chart = ft_calloc(1, sizeof(t_map));
	if (!info->chart)
		return (cbd_error(ERR_MEMORY), FAILURE);
	i = *idx;
	while (line[i])
		i++;
	info->chart->map = ft_calloc((i - *idx) + 1, sizeof(char *));
	if (!info->chart->map)
		return (cbd_error(ERR_MEMORY), FAILURE);
	i = 0;
	while (line[*idx])
	{
		info->chart->map[i] = ft_strdup(line[*idx]);
		if (info->chart->map[i] == NULL)
			return (cbd_error(ERR_MEMORY), FAILURE);
		i++;
		(*idx)++;
	}
	return (SUCCESS);
}

int	parser(int fd, t_cub3d *info)
{
	char	**filelines;
	char	*fileline;
	ssize_t	idx;

	idx = 0;
	if (fd == -1)
		return (FAILURE);
	fileline = read_fd(fd);
	filelines = ft_split(fileline, '\n');
	if (filelines == NULL)
		return (cbd_error(ERR_MEMORY), FAILURE);
	ft_bzero(info, sizeof(t_cub3d));
	if (get_data(info, fileline, &idx))
		return (cbd_free_info(info), FAILURE);
	if (get_mappi(info, filelines, &idx))
		return (cbd_free_info(info), FAILURE);
// set_default(info);
	free(filelines);
	free(fileline);
	if (parse_map(info->chart) == FAILURE)
		return (print_info(info), cbd_free_info(info), FAILURE);
	if (check_path(info->chart) == FAILURE)
		return (print_info(info), cbd_free_info(info), FAILURE);
	if (get_mlx(info))
		return (cbd_free_info(info), FAILURE);
	print_info(info);
	return (SUCCESS);
}
