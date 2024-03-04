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

#include "Cub3d.h"
#include "CBDparser.h"

#include "libft.h"

#include <sys/types.h>

bool	get_map(t_map *chart, char *line, ssize_t *idx)
{
	ssize_t	i;
	ssize_t	line_count;

	*idx = ft_strskipis(&line[*idx], ft_isspace);
	line_count= 0;
	i = *idx;
	while (line[i])
	{
		if (line[i] == '\n')
			line_count++;
		i++;
	}
	chart->map = ft_calloc(line_count + 1, sizeof(char *));
	if (!chart->map)
		return (cbd_error(ERR_MEMORY), FAILURE);
	i = 0;
	while (line[*idx]) // && i < line_count)
	{
		chart->map[i] = ft_strdup(line[*idx]);
		if (chart->map[i] == NULL)
			return (cbd_error(ERR_MEMORY), FAILURE);
		i++;
		// (*idx)++;
	}
	return (SUCCESS);
}
