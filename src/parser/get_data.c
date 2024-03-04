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

static const char	*g_id_str[TYPE_ID_MAX] = {
[TYPE_ID_NORTH] = "NO",
[TYPE_ID_SOUTH] = "SO",
[TYPE_ID_WEST] = "WE",
[TYPE_ID_EAST] = "EA",
[TYPE_ID_FLOOR] = "F",
[TYPE_ID_CEILING] = "C"};

static uint32_t	get_colour(char *str, int *err)
{
	size_t		start;
	int			i;
	uint32_t	val;
	uint32_t	ret;

	start = ft_strskipis(str, ft_isspace);
	i = 2;
	ret = 255;
	while (i >= 0 && *err == SUCCESS)
	{
		val = ft_atoi(&str[start]);
		if (val < 0 || val > 255)
			*err = ERR_PARSE_RGB;
		ret += (val << (8 * (i + 1)));
		start += ft_strskipis(&str[start], ft_isdigit);
		if (i != 0 && str[start] != ',')
			*err = ERR_PARSE_FORMAT;
		start++;
		i--;
	}
#ifdef LOG
	ft_printf("get_colour: %X\n", ret);
#endif
	return (ret);
}

static char	*get_texture(char *str, int *err)
{
	size_t	start;
	size_t	end;
	char	*ret;

	start = ft_strskipis(str, ft_isspace);
	end = ft_strskipis(&str[start], ft_ispath);
	ret = ft_substr(str, start, end - start);
	if (!ret)
		*err = ERR_MEMORY;
	else if (!ft_stris(ret, ft_ispath))
		*err = ERR_PARSE_PATH;
#ifdef LOG
	ft_printf("get_texture: %s\n", ret);
#endif
	return (ret);
}

static bool	check_filled(t_cub3d *info, t_type_id id)
{
	if (id == TYPE_ID_NORTH)
		return (ft_ternary(info->text_no != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_SOUTH)
		return (ft_ternary(info->text_so != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_WEST)
		return (ft_ternary(info->text_we != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_EAST)
		return (ft_ternary(info->text_ea != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_FLOOR)
		return (ft_ternary(info->col_fl != 0, FAILURE, SUCCESS));
	else if (id == TYPE_ID_CEILING)
		return (ft_ternary(info->col_ce != 0, FAILURE, SUCCESS));
	return (FAILURE);
}

static bool	set_infovalue(t_cub3d *info, t_type_id id, char *str)
{
	int	err;

	err = SUCCESS;
	if (check_filled(info, id))
		err = ERR_PARSE_FILLED;
	else
	{
		if (id == TYPE_ID_NORTH)
			info->text_no = get_texture(str, &err);
		else if (id == TYPE_ID_SOUTH)
			info->text_so = get_texture(str, &err);
		else if (id == TYPE_ID_WEST)
			info->text_we = get_texture(str, &err);
		else if (id == TYPE_ID_EAST)
			info->text_ea = get_texture(str, &err);
		else if (id == TYPE_ID_FLOOR)
			info->col_fl = get_colour(str, &err);
		else if (id == TYPE_ID_CEILING)
			info->col_ce = get_colour(str, &err);
	}
	cbd_error(err);
	return (err);
}

static t_type_id	get_identifier(char *str, ssize_t *idx)
{
	ssize_t	id_idx;

	id_idx = TYPE_ID_NORTH;
	while (id_idx != TYPE_ID_MAX)
	{
		if (!ft_strncmp(&str[*idx], g_id_str[id_idx],
				ft_strlen(g_id_str[id_idx])))
			break ;
		id_idx++;
	}
	*idx += ft_strlen(g_id_str[id_idx]);
	return (id_idx);
}

bool	get_data(t_cub3d *info, char *lines, ssize_t *idx)
{
	t_type_id	type_id;
	size_t		data_idx;
	
	data_idx = 0;
	while (lines[*idx] && data_idx < 6)
	{
		*idx += ft_strskipis(&lines[*idx], ft_isspace);
		type_id = get_identifier(lines, idx);
		if (type_id == TYPE_ID_MAX)
			return (cbd_error(ERR_PARSE_ID), FAILURE);
		*idx += ft_strskipis(&lines[*idx], ft_isspace);
		if (set_infovalue(info, type_id, &lines[*idx]))
			return (FAILURE);
		*idx = ft_strchr(&lines[*idx], '\n') - lines;	//	rn it just ignores anything after 
														//	the first two tokens. 
														//!	also pointer arithmatic bad?
		data_idx++;
	}
		ft_printf("\t-=- FILE -=-\n%s\n\t-=- END FILE -=-\n", &lines[*idx]);
	return (SUCCESS);
}
