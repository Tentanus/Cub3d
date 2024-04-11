/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CBDminimap.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 15:36:03 by mweverli      #+#    #+#                 */
/*   Updated: 2024/03/20 15:36:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBDMINIMAP_H
# define CBDMINIMAP_H

# include "Cub3d.h"

// KEY_HOOK
void	minimap_key_hook(mlx_key_data_t keydata, void *param);

// PLAYER
void	fill_player(t_minimap *mini, t_raycaster *raycaster);

// UTILS 
void	tile_to_window(t_minimap *mini, size_t x, size_t y, uint32_t col);
void	b_tile_to_window(t_minimap *mini, size_t x, size_t y, uint32_t col);

#endif
