/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarteld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:30:38 by abarteld          #+#    #+#             */
/*   Updated: 2024/02/27 19:30:40 by abarteld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"
#include "libft.h"

static bool	is_player_spawn(char point)
{
	if (point == 'N' || point == 'E' || point == 'S' || point == 'W')
		return (true);
	return (false);
}

static bool	set_player_values(t_map *chart)
{
	int		i;
	int		j;

	i = 0;
	while (chart->map[i])
	{
		j = 0;
		while (chart->map[i][j])
		{
			if (is_player_spawn(chart->map[i][j]) == true)
			{
				if (chart->player_direction)
					return (FAILURE);
				chart->py = i;
				chart->px = j;
				chart->player_direction = chart->map[i][j];
			}
			j++;
		}
		i++;
	}
	if (!chart->player_direction)
		return (FAILURE);
	return (SUCCESS);
}

static bool	set_map_values(t_map *chart)
{
	int	i;
	int	j;
	int	max_x;

	if (!chart->map)
		return (FAILURE);
	i = 0;
	max_x = 0;
	while (chart->map[i])
	{
		j = 0;
		while (chart->map[i][j])
			j++;
		if (j == 0)
			return (FAILURE);
		if (j > max_x)
			max_x = j;
		i++;
	}
	if (i < 3 || max_x < 3)
		return (FAILURE);
	chart->max_y = i - 1;
	chart->max_x = max_x - 1;
	return (SUCCESS);
}

bool	parse_map(t_map *chart)
{
	int	i;

	i = 0;
	while (chart->map[i])
	{
		if (ft_strsubset(chart->map[i], MAP_CHARACTER))
			return (FAILURE);
		i++;
	}
	if (set_player_values(chart) == FAILURE)
		return (FAILURE);
	if (set_map_values(chart) == FAILURE)
		return (FAILURE);
	chart->map_invalid = false;
	chart->map_complete = false;
	return (SUCCESS);
}
