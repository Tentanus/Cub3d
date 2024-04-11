/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:31:09 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/13 19:31:11 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CBDerror.h"
#include "Cub3d.h"
#include "CBDparser.h"

#include "libft.h"

#include <sys/types.h>

static size_t	get_map_count_lines(char *line, ssize_t *idx)
{
	size_t	line_count;
	size_t	i;

	line_count = 0;
	i = *idx;
	while (line[i])
	{
		if (line[i] == '\n')
			line_count++;
		i++;
	}
	if (i > 0 && line[i - 1] != '\n')
		line_count++;
	return (line_count);
}

static char	*get_map_extract_line(char *line, ssize_t *idx)
{
	char	*ret;
	ssize_t	len;

	len = *idx;
	while (line[len] && line[len] != '\n')
		len++;
	ret = ft_substr(line, *idx, len - *idx + 1);
	if (ret == NULL)
		return (NULL);
	if (ret[len - *idx] == '\n')
		ret[len - *idx] = '\0';
	*idx = len + 1;
	return (ret);
}

static char	**get_map_line(char *line, ssize_t *idx)
{
	size_t	line_count;
	size_t	i;
	char	**ret;

	line_count = get_map_count_lines(line, idx);
	ret = ft_calloc(line_count + 1, sizeof (char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < line_count)
	{
		ret[i] = get_map_extract_line(line, idx);
		if (ret[i] == NULL)
			return (ft_split_free(ret), NULL);
		i++;
	}
	return (ret);
}

bool	get_map(t_cub3d *info, char *line, ssize_t *idx)
{
	info->chart = ft_calloc(1, sizeof(t_map));
	if (!info->chart)
		return (cbd_error(ERR_MEMORY), FAILURE);
	*idx += ft_strskipchar(&line[*idx], '\n');
	info->chart->map = get_map_line(line, idx);
	if (info->chart->map == NULL)
		return (cbd_error(ERR_MEMORY), FAILURE);
	return (SUCCESS);
}
