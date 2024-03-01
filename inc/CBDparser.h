/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CBDparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:46:23 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/13 19:46:24 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBDPARSER_H
# define CBDPARSER_H

# include "get_next_line.h"

# include <stdbool.h>

# define MAP_CHARACTER " 01NSWE"
// maps can only contain spaces, meaning no other whitespace characters;
# define READ_CHUNK 10000 //or a cool number


typedef struct s_map
{
	char	**map;				// lines are filled with ' ' to make the map rectangular
	
	int		px;					// index, the 'x' of the player spawn
	int		py;					// index, the 'y' of the player spawn
	char	player_direction;	// the direction the player faces in at spawn
	int		max_x;				// index, the length of the longest line in the map
	int		max_y;				// index, the number of lines in the map
	
	bool	map_invalid;		// set to true after floodfill confirms the map is not (fully) enclosed by walls
	bool	map_complete;		// set to true when the map is fully floodfilled
}	t_map;

typedef enum e_type_id
{
	TYPE_ID_NORTH,
	TYPE_ID_SOUTH,
	TYPE_ID_WEST,
	TYPE_ID_EAST,
	TYPE_ID_FLOOR,
	TYPE_ID_CEILING,
	TYPE_ID_MAX
}	t_type_id;

typedef struct s_cub3d	t_cub3d;

int		parser(int fd, t_cub3d *info);

bool	get_data(t_cub3d *info, char **lines, ssize_t *idx);
bool	get_map(t_cub3d *info, char **lines, ssize_t *idx);
bool	get_mlx(t_cub3d *info);

bool	parse_map(t_map *chart);
bool	check_path(t_map *chart);

#endif // !CBDPARSER_H
