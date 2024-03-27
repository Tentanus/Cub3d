/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_player.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 15:36:03 by mweverli      #+#    #+#                 */
/*   Updated: 2024/03/20 15:36:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "CBDminimap.h"
#include "Cub3d.h"

void	fill_player(t_minimap *mini, t_raycaster *raycaster)
{
	//TODO: Remove the 0.5
	const uint32_t	tile = mini->tile_size;
	const double	mini_pos_x = ((raycaster->player_pos.x + 0.5) * tile) \
		- (mini->player_size >> 1);
	const double	mini_pos_y = ((raycaster->player_pos.y + 0.5) * tile) \
		- (mini->player_size >> 1);

	circle_to_window(mini, mini_pos_x, mini_pos_y, mini->player_size, 0xFF0000FF);
}
