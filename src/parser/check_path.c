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

// potential rendering optimization, by cutting out all parts \
// of the map the player can't reach/see potential clean map \
// probs doesn't need to be a bool
static bool	floodfill(t_map *chart, char **map, int x, int y)
{
	if (chart->map_invalid == true)
		return (FAILURE);
	if (map[y][x] == '1')
		return (SUCCESS);
	if (!map[y][x] || map[y][x] == ' ' || x + 1 > chart->max_x || \
		y + 1 > chart->max_y || x == 0 || y == 0)
	{
		chart->map_invalid = true;
		return (cbd_error(ERR_MAP_ENCLOSED), FAILURE);
	}
	if (map[y][x] == '0')
	{
		map[y][x] = '1';
		floodfill(chart, map, x + 1, y);
		floodfill(chart, map, x, y + 1);
		floodfill(chart, map, x - 1, y);
		floodfill(chart, map, x, y - 1);
		return (SUCCESS);
	}
	return (FAILURE);
}

static bool	flood_loop(t_map *chart, char **map)
{
	int	i;
	int	j;

	while (!chart->map_complete && !chart->map_invalid && map)
	{
		chart->map_complete = true;
		i = 0;
		while (map[i])
		{
			j = 0;
			while (map[i][j])
			{
				if (map[i][j] == '0')
				{
					chart->map_complete = false;
					floodfill(chart, map, j, i);
					if (chart->map_invalid)
						return (FAILURE);
				}
				j++;
			}
			i++;
		}
	}
	return (SUCCESS);
}

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

bool	check_path(t_map *chart)
{
	char	**map;

	map = copy_array(chart->map);
	if (map == NULL)
		return (FAILURE);
	map[chart->py][chart->px] = '0';
	if (floodfill(chart, map, chart->px, chart->py) == FAILURE || \
		chart->map_invalid)
		return (ft_split_free(map), FAILURE);
	if (flood_loop(chart, map) == FAILURE)
		return (ft_split_free(map), FAILURE);
print_map(map);
	ft_split_free(map);
	return (SUCCESS);
}
