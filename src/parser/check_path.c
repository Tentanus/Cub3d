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

static bool	is_player_spawn(char point)
{
	if (point == 'N' || point == 'E' || point == 'S' || point == 'W')
		return (true);
	return (false);
}

static bool	set_player_values(char **map, int *x, int *y)
{
	int	i;
	int	j;

	if (!map)
		return (FAILURE);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_spawn(map[i][j]) == true)
			{
				(*y) = i;
				(*x) = j;
				return (SUCCESS);
			}
			j++;
		}
		i++;
	}
	return (FAILURE);
}

static bool	set_map_values(char **map, int *x, int *y)
{
	int	i;
	int	j;
	int	max_x;

	if (!map)
		return (FAILURE);
	i = 0;
	max_x = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max_x)
			max_x = j;
		i++;
	}
	(*y) = i;
	(*x) = max_x;
	return (SUCCESS);
}

// find starting position
// floodfill from starting position
// loop that finds remaining 0's, floodfills from there
// error on encountering spaces

bool	floodfill(t_map *chart, char **map, int x, int y) // probs doesn't need to be a bool
{
	if (chart->flood_valid == false)
		return (FAILURE);
	if (map[y][x] == '1')
		return (SUCCESS);
	if (map[y][x] == ' ' || x + 1 > chart->max_x || y + 1 > chart->max_y || x == 0 || y == 0)
	{
printf("map be failed\n");
		chart->flood_valid = false;
		return (FAILURE);
	}
	// if (map[y][x] == '1')
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

static bool flood_loop(t_map *chart)
{
	// int	i;
	// int	j;

	// while (1)
	// {
	// 	i = 0
	// 	while (map[i])
	// 	{
			
	// 	}

	// }
	return (SUCCESS);
}

bool	check_path(t_cub3d *info)
{
	t_map	*chart; //take from struct
	char	**map;

	chart = malloc(sizeof(t_map)); //take from struct
	chart->flood_valid = true; // init when the t_map is made
	map = info->map; //change to copy map
	if (set_player_values(map, &chart->px, &chart->py) == FAILURE) //take from struct
		return (FAILURE);
	if (set_map_values(map, &chart->max_x, &chart->max_y) == FAILURE) //take from struct
		return (FAILURE);
printf("Player starts at x=%d/y=%d\n", chart->px, chart->py);
printf("Map edges are x=%d/y=%d.\n", chart->max_x, chart->max_y);
write(1, "SEGGY?\n", 7);
	map[chart->py][chart->px] = '0';
	if (floodfill(chart, map, chart->px, chart->py) == FAILURE || chart->flood_valid == false)
		return (print_info(info), FAILURE); //change out print info
	//loop over 0's
	if (flood_loop(chart) == FAILURE) // loops over the map, floodfilling remaining 0's into 1's until there are none left
		return (print_info(info), FAILURE); //change out print info
	return (SUCCESS);
}
