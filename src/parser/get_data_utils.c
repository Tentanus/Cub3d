/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:31:00 by mweverli          #+#    #+#             */
/*   Updated: 2024/04/10 19:31:03 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "CBDparser.h"
#include "libft.h"

uint32_t	get_colour(char *str, ssize_t *idx, int *err)
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
	return (ret);
}

char	*get_texture(char *str, ssize_t *idx, int *err)
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
	return (ret);
}
