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

#include "Cub3d.h"
#include "MLX42.h"
#include "libft.h"

void	cbd_free_chart(t_cub3d *info)
{
	if (info->chart)
	{
		ft_split_free(info->chart->map);
		free(info->chart);
		info->chart = NULL;
	}
}

void	cbd_free_param(t_cub3d *info)
{
	if (info->param)
	{
		if (info->param->text_no)
			free(info->param->text_no);
		if (info->param->text_so)
			free(info->param->text_so);
		if (info->param->text_we)
			free(info->param->text_we);
		if (info->param->text_ea)
			free(info->param->text_ea);
		free(info->param);
		info->param = NULL;
	}
}

void	cbd_free_raycaster(t_cub3d *info)
{
	if (info->raycaster)
	{
		cbd_free_texture(info->raycaster, 3);
		ft_split_free(info->raycaster->map);
		free(info->raycaster);
		info->raycaster = NULL;
	}
}

void	cbd_free_minimap(t_cub3d *info)
{
	free(info->minimap);
	info->minimap = NULL;
}

void	cbd_free_info(t_cub3d *info)
{
	cbd_free_chart(info);
	cbd_free_param(info);
	cbd_free_raycaster(info);
	cbd_free_minimap(info);
}
