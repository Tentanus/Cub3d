/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:43:47 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/13 19:43:48 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CBDraycaster.h"
#include "Cub3d.h"
#include "MLX42.h"
#include "libft.h"

void	cbd_free_chart(t_cub3d *info)
{
	ft_split_free(info->chart->map);
	info->chart = NULL;
}

void	cbd_free_param(t_cub3d *info)
{
	free(info->param->text_no);
	free(info->param->text_so);
	free(info->param->text_we);
	free(info->param->text_ea);
	info->param = NULL;
}

void	cbd_free_raycaster(t_cub3d *info)
{
	ft_split_free(info->raycaster->map);
		
	info->raycaster = NULL;
}

void	cbd_free_minimap(t_cub3d *info)
{

	info->minimap = NULL;
}

void	cbd_free_texture(t_raycaster *raycaster, int idx)
{
	while (idx--)
	{
		mlx_delete_texture(raycaster->textures[idx]);
		raycaster->textures[idx] = NULL;
	}
}

void	cbd_free_info(t_cub3d *info)
{
	if (info->chart)
		cbd_free_chart(info);
	if (info->param)
		cbd_free_param(info);
	if (info->raycaster)
		cbd_free_raycaster(info);
	if (info->minimap)
		cbd_free_minimap(info);
}
