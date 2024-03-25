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

static char	*read_fd(int fd)
{
	char	*line;
	char	*tmp;

	line = ft_calloc(READ_CHUNK, sizeof(char));
	if (line == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	if (read(fd, line, READ_CHUNK) != READ_CHUNK)
	{
		close(fd);
		return (line);
	}
	tmp = ft_calloc(READ_CHUNK, sizeof(char));
	if (tmp == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	while (read(fd, tmp, READ_CHUNK) == READ_CHUNK)
	{
		line = ft_strjoin_fs1(line, tmp);
		if (line == NULL)
			return (cbd_error(ERR_MEMORY), NULL);
	}
	close(fd);
	free(tmp);
	return (line);
}

bool	parser(int fd, t_cub3d *info)
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
	if (check_path(info->chart) == FAILURE)
		return (print_info(info), cbd_free_info(info), FAILURE);
// print_info(info);
// print_map(info->chart->map);
	return (SUCCESS);
}
