/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarteld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:35:16 by abarteld          #+#    #+#             */
/*   Updated: 2024/02/20 16:35:17 by abarteld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"
#include "libft.h"

char	**copy_array(char **arr)
{
	char	**copy;
	int		i;

	if (arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (copy == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	copy[i] = NULL;
	i = 0;
	while (arr[i])
	{
		copy[i] = ft_strdup(arr[i]);
		if (copy[i] == NULL)
		{
			ft_split_free(copy);
			return (cbd_error(ERR_MEMORY), NULL);
		}
		i++;
	}
	return (copy);
}

static char	**copy_array_padded(char **arr, int len)
{
	char	**copy;
	int		i;

	if (arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (copy == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	copy[i] = NULL;
	i = 0;
	while (arr[i])
	{
		copy[i] = ft_calloc(len + 1, sizeof(char));
		if (copy[i] == NULL)
		{
			ft_split_free(copy);
			return (cbd_error(ERR_MEMORY), NULL);
		}
		ft_strlcpy(copy[i], arr[i], len + 1);
		i++;
	}
	return (copy);
}

bool	check_square(const t_map chart, char **map, int y, int x)
{
	if (map[y][x] != '0')
		return (SUCCESS);
	if (x + 1 > chart.max_x || y + 1 > chart.max_y || x == 0 || y == 0)
		return (FAILURE);
	if (map[y + 1][x] == ' ' || map[y - 1][x] == ' ' || \
		map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
		return (FAILURE);
	if (map[y + 1][x] == '\0' || map[y - 1][x] == '\0' || \
		map[y][x + 1] == '\0' || map[y][x - 1] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

bool	check_path(t_map *chart)
{
	char	**map;
	int		i;
	int		j;

	map = copy_array_padded(chart->map, chart->max_x + 1);
	if (map == NULL)
		return (FAILURE);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_square(*chart, map, i, j) == FAILURE)
				return (ft_split_free(map), \
					cbd_error(ERR_MAP_ENCLOSED), FAILURE);
			j++;
		}
		i++;
	}
	ft_split_free(map);
	return (SUCCESS);
}
