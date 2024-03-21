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

# include <stdbool.h>
# include <sys/types.h>

# define MAP_CHARACTER " 01NSWE"
// maps can only contain spaces, meaning no other whitespace characters;
# define READ_CHUNK 10000 //or a cool number

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
typedef struct s_map	t_map;

bool	get_data(t_cub3d *info, char *lines, ssize_t *idx);
bool	get_map(t_cub3d *info, char *line, ssize_t *idx);
bool	get_mlx(t_cub3d *info); // move to raycaster struct

bool	parse_map(t_map *chart);
bool	check_path(t_map *chart);

#endif // !CBDPARSER_H
