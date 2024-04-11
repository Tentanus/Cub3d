/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logprinter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:43:39 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/13 19:43:40 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "libft.h"
#include <unistd.h>

void	print_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map)
		ft_printf("| NO MAP: \n|\n");
	else
	{
		ft_printf("| MAP: \n|\n");
		while (map[i])
		{
			ft_printf("|\t%u |\t%s|\n", i, map[i]);
			i++;
		}
		ft_printf("|\n");
	}
}

void	print_info(t_cub3d *info)
{
	ft_printf("\t-=- PRINTING INFO -=-\n\n");
	if (info == NULL)
	{
		ft_putendl_fd("\n -=- NO INFO FOUND -=-\n", STDERR_FILENO);
		return ;
	}
	print_map(info->chart->map);
	ft_printf("| TEXTURE & COLLOUR:\n");
	ft_printf("|\tTEXTURE  NORTH:  \t%s\n", info->param->text_no);
	ft_printf("|\tTEXTURE  SOUTH:  \t%s\n", info->param->text_so);
	ft_printf("|\tTEXTURE  WEST:   \t%s\n", info->param->text_we);
	ft_printf("|\tTEXTURE  EAST:   \t%s\n", info->param->text_ea);
	ft_printf(\
"|\tCOLOUR   FLOOR:  \t%X\t\t%b\n", info->param->col_fl, info->param->col_fl);
	ft_printf(\
"|\tCOLOUR   CEILING:\t%X\t\t%b\n", info->param->col_ce, info->param->col_ce);
	ft_printf("\n\t-=- FINISHED -=-\n\n");
}
