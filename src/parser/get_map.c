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

bool	get_map(t_cub3d *info, char **line, ssize_t *idx)
{
	ssize_t	i;

	i = *idx;
	while (line[i])
		i++;
	info->map = ft_calloc((i - *idx) + 1, sizeof(char *));
	if (!info->map)
		return (cbd_error(ERR_MEMORY), FAILURE);
	i = 0;
	while (line[*idx])
	{
		info->map[i] = ft_strdup(line[*idx]);
		if (info->map[i] == NULL)
			return (cbd_error(ERR_MEMORY), FAILURE);
		i++;
		(*idx)++;
	}
	return (SUCCESS);
}
