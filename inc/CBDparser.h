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
// maps can only contain spaces, meaning no other whitespace
// characters;

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

#endif // !CBDPARSER_H
