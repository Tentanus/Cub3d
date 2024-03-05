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

bool	get_map(t_cub3d *info, char *line, ssize_t *idx)
{
	info->chart = ft_calloc(1, sizeof(t_map));
	if (!info->chart)
		return (cbd_error(ERR_MEMORY), FAILURE);
	info->chart->map = ft_split(&line[*idx], '\n');
	if (info->chart->map == NULL)
		return (FAILURE);	
	return (SUCCESS);
}
