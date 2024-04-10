/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:31:00 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/13 19:31:03 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "CBDparser.h"
#include "libft.h"

#include <sys/types.h>

static bool	check_filled(t_cub3d *info, t_type_id id)
{
	if (id == TYPE_ID_NORTH)
		return (ft_ternary(info->param->text_no != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_SOUTH)
		return (ft_ternary(info->param->text_so != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_WEST)
		return (ft_ternary(info->param->text_we != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_EAST)
		return (ft_ternary(info->param->text_ea != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_FLOOR)
		return (ft_ternary(info->param->col_fl != 0, FAILURE, SUCCESS));
	else if (id == TYPE_ID_CEILING)
		return (ft_ternary(info->param->col_ce != 0, FAILURE, SUCCESS));
	return (FAILURE);
}

static bool	set_infovalue(t_cub3d *info, t_type_id id, char *str, ssize_t *idx)
{
	int	err;

	err = SUCCESS;
	if (check_filled(info, id))
		err = ERR_PARSE_FILLED;
	else
	{
		if (id == TYPE_ID_NORTH)
			info->param->text_no = get_texture(str, idx, &err);
		else if (id == TYPE_ID_SOUTH)
			info->param->text_so = get_texture(str, idx, &err);
		else if (id == TYPE_ID_WEST)
			info->param->text_we = get_texture(str, idx, &err);
		else if (id == TYPE_ID_EAST)
			info->param->text_ea = get_texture(str, idx, &err);
		else if (id == TYPE_ID_FLOOR)
			info->param->col_fl = get_colour(str, idx, &err);
		else if (id == TYPE_ID_CEILING)
			info->param->col_ce = get_colour(str, idx, &err);
	}
	cbd_error(err);
	return (err);
}

static t_type_id	get_identifier(char *str, ssize_t *idx)
{
	const char	*id_array[TYPE_ID_MAX] = {
	[TYPE_ID_NORTH] = "NO",
	[TYPE_ID_SOUTH] = "SO",
	[TYPE_ID_WEST] = "WE",
	[TYPE_ID_EAST] = "EA",
	[TYPE_ID_FLOOR] = "F",
	[TYPE_ID_CEILING] = "C"};
	ssize_t		id_idx;

	id_idx = TYPE_ID_NORTH;
	while (id_idx != TYPE_ID_MAX)
	{
		if (!ft_strncmp(&str[*idx], id_array[id_idx],
				ft_strlen(id_array[id_idx])))
			break ;
		id_idx++;
	}
	if (id_array[id_idx] != NULL)
		*idx += ft_strlen(id_array[id_idx]);
	return (id_idx);
}

bool	get_data(t_cub3d *info, char *lines, ssize_t *idx)
{
	t_type_id	type_id;
	size_t		data_idx;

	info->param = ft_calloc(1, sizeof(t_param));
	if (info->param == NULL)
		return (cbd_error(ERR_MEMORY), NULL);
	data_idx = 0;
	while (lines[*idx] && data_idx < 6)
	{
		*idx += ft_strskipis(&lines[*idx], ft_isspace);
		type_id = get_identifier(lines, idx);
		if (type_id == TYPE_ID_MAX)
			return (cbd_error(ERR_PARSE_ID), FAILURE);
		*idx += ft_strskipis(&lines[*idx], ft_isspace);
		if (set_infovalue(info, type_id, lines, idx))
			return (FAILURE);
		if (lines[*idx] != '\n')
			return (cbd_error(ERR_PARSE_TRAIL), FAILURE);
		*idx = ft_strchr(&lines[*idx], '\n') - lines;
		data_idx++;
	}
	if (data_idx != 6 && !lines[*idx])
		return (cbd_error(ERR_PARSE_FORMAT), FAILURE);
	return (SUCCESS);
}
