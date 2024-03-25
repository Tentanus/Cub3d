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
#include "libft.h"

void	cbd_free_info(t_cub3d *info)
{
	if (info->chart)
	{
		if (info->chart->map)
			ft_split_free(info->chart->map);
		free(info->chart);
	}
	if (info->param->text_no)
		free(info->param->text_no);
	if (info->param->text_so)
		free(info->param->text_so);
	if (info->param->text_we)
		free(info->param->text_we);
	if (info->param->text_ea)
		free(info->param->text_ea);
}
