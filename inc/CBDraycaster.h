/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CBDraycaster.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarteld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:38:37 by abarteld          #+#    #+#             */
/*   Updated: 2024/03/25 13:38:38 by abarteld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBDRAYCASTER_H
# define CBDRAYCASTER_H

// # include "Cub3d.h"
typedef struct s_raycaster	t_raycaster;
typedef struct s_parameters	t_param;

// double dirX = -1.0, dirY = 0.0; //initial direction vector: WEST
// double dirX = 1.0, dirY = 0.0; //initial direction vector: EAST



typedef enum e_textures
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_textures;

bool	get_mlx(t_raycaster *raycaster);
bool	get_image(t_raycaster *raycaster);
bool	load_textures(t_raycaster *raycaster, const t_param param);

#endif // !CBDRAYCASTER_H
