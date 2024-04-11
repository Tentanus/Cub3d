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
	int		r;

	line = ft_calloc(READ_CHUNK + 1, sizeof(char));
	if (line == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	tmp = ft_calloc(READ_CHUNK + 1, sizeof(char));
	if (tmp == NULL)
		return (free(line), cbd_error(ERR_MEMORY), NULL);
	r = read(fd, line, READ_CHUNK);
	while (r == READ_CHUNK)
	{
		r = read(fd, tmp, READ_CHUNK);
		if (r == -1)
			break ;
		tmp[r] = '\0';
		line = ft_strjoin_fs1(line, tmp);
		if (line == NULL)
			return (free(tmp), cbd_error(ERR_MEMORY), NULL);
	}
	free(tmp);
	if (r == -1)
		return (free(line), cbd_error(ERR_READ), NULL);
	return (line);
}

bool	parser(int fd, t_cub3d *info)
{
	char	*fileline;
	ssize_t	idx;

	if (fd == -1)
		return (FAILURE);
	fileline = read_fd(fd);
	close(fd);
	if (fileline == NULL)
		return (FAILURE);
	ft_bzero(info, sizeof(t_cub3d));
	idx = 0;
	if (get_data(info, fileline, &idx))
		return (cbd_free_info(info), FAILURE);
	if (get_map(info, fileline, &idx))
		return (cbd_free_info(info), FAILURE);
	free(fileline);
	if (parse_map(info->chart) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	if (check_path(info->chart) == FAILURE)
		return (cbd_free_info(info), FAILURE);
	return (SUCCESS);
}
