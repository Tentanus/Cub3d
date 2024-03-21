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

static uint32_t	get_colour(char *str, ssize_t *idx, int *err)
{
	size_t		start;
	int			i;
	uint32_t	val;
	uint32_t	ret;

	start = ft_strskipis(&str[*idx], ft_isspace);
	i = 2;
	ret = 255;
	while (i >= 0 && *err == SUCCESS)
	{
		val = ft_atoi(&str[*idx + start]);
		if (val < 0 || val > 255)
			*err = ERR_PARSE_RGB;
		ret += (val << (8 * (i + 1)));
		start += ft_strskipis(&str[*idx + start], ft_isdigit);
		if (i != 0 && str[*idx + start] != ',')
			*err = ERR_PARSE_FORMAT;
		start++;
		i--;
	}
	*idx = ft_strskipset(&str[*idx], "1234567890,") - str;
#ifdef LOG
	ft_printf("get_colour: %X\n", ret);
#endif
	return (ret);
}

static char	*get_texture(char *str, ssize_t *idx, int *err)
{
	size_t	start;
	size_t	end;
	char	*ret;

	start = ft_strskipis(&str[*idx], ft_isspace);
	end = ft_strskipis(&str[*idx + start], ft_ispath);
	ret = ft_substr(&str[*idx], start, end - start);
	if (!ret)
		*err = ERR_MEMORY;
	*idx += ft_strskipis(&str[*idx], ft_ispath);
#ifdef LOG
	ft_printf("get_texture: %s\n", ret);
#endif
	return (ret);
}

static bool	check_filled(t_cub3d *info, t_type_id id)
{
	if (id == TYPE_ID_NORTH)
		return (ft_ternary(info->par->text_no != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_SOUTH)
		return (ft_ternary(info->par->text_so != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_WEST)
		return (ft_ternary(info->par->text_we != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_EAST)
		return (ft_ternary(info->par->text_ea != NULL, FAILURE, SUCCESS));
	else if (id == TYPE_ID_FLOOR)
		return (ft_ternary(info->par->col_fl != 0, FAILURE, SUCCESS));
	else if (id == TYPE_ID_CEILING)
		return (ft_ternary(info->par->col_ce != 0, FAILURE, SUCCESS));
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
			info->par->text_no = get_texture(str, idx, &err);
		else if (id == TYPE_ID_SOUTH)
			info->par->text_so = get_texture(str, idx, &err);
		else if (id == TYPE_ID_WEST)
			info->par->text_we = get_texture(str, idx, &err);
		else if (id == TYPE_ID_EAST)
			info->par->text_ea = get_texture(str, idx, &err);
		else if (id == TYPE_ID_FLOOR)
			info->par->col_fl = get_colour(str, idx, &err);
		else if (id == TYPE_ID_CEILING)
			info->par->col_ce = get_colour(str, idx, &err);
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
	if (g_id_str[id_idx] != NULL)
		*idx += ft_strlen(g_id_str[id_idx]);
	return (id_idx);
}

bool	get_data(t_cub3d *info, char *lines, ssize_t *idx)
{
	t_type_id	type_id;
	size_t		data_idx;

	info->par = ft_calloc(1, sizeof(t_param));
	if (info->par == NULL)
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
	return (SUCCESS);
}
