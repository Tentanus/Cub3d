
#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"

#include "libft.h"

static const char *g_id_str[TYPE_ID_MAX] = {
	[TYPE_ID_NORTH] = "NO", [TYPE_ID_SOUTH] = "SO",	 [TYPE_ID_WEST] = "WE",
	[TYPE_ID_EAST] = "EA",	[TYPE_ID_CEILING] = "C", [TYPE_ID_FLOOR] = "F"};

static int32_t get_colour(char *line)
{
}

static char *get_path(char *line)
{
	size_t word_start;
	size_t word_end;
	char *ret;

	word_start = 2;
	if (!ft_isspace(line[word_start]))
		return (cbd_error(ERR_PARSE_ID), NULL);
	word_start += ft_strskipis(&line[word_start], ft_isspace);
	word_end = word_start + ft_strskipis(&line[word_start], ft_ispath);
	if (word_end != ft_strlen(line))
		return (cbd_error(ERR_PARSE_FORMAT), NULL);
	ret = ft_substr(line, word_start, (word_end - word_start));
	if (!ret)
		return (cbd_error(ERR_MEMORY), NULL);
	return (ret);
}

static bool set_value(t_cub3d *info, char *str, t_type_id id)
{
	char *path;
	int col;

	if (id == TYPE_ID_MAX)
		return (cbd_error(ERR_PARSE_ID), false);
	path = get_path(str, id);
	if (!path)
		return (false);
	if (id == TYPE_ID_NORTH)
		info->text_no = path;
	else if (id == TYPE_ID_SOUTH)
		info->text_so = path;
	else if (id == TYPE_ID_WEST)
		info->text_we = path;
	else if (id == TYPE_ID_EAST)
		info->text_ea = path;
	else if (id == TYPE_ID_CEILING)
		info->col_ce = (int32_t)path;
	else if (id == TYPE_ID_FLOOR)
		info->col_fl = (int32_t)path;
	return (true);
}

t_type_id get_type_id(char *str)
{
	size_t i;

	i = 0;
	while (i < TYPE_ID_MAX)
		if (!ft_strncmp(str, g_id_str[i], ft_strlen(g_id_str[i])))
			break;
	return (i);
}

static bool fill_text_col(char **file, t_cub3d *info)
{
	size_t file_i;
	size_t str_i;
	t_type_id id;

	file_i = 0;
	while (file[file_i])
	{
		if (!ft_strsubset(file[file_i], MAP_CHARACTER))
		{
			str_i = ft_skip_whitespace(file[file_i]);
			id	  = get_type_id(&file[file_i][str_i]);
			if (!set_value(info, &file[file_i][str_i], id))
				return (FAILURE);
		}
		file_i++;
	}
	return (SUCCESS);
}

static void fill_map(char **file, t_cub3d *info)
{
	size_t i;

	i = 0;
	while (file[i])
		if (ft_strsubset(file[i++], MAP_CHARACTER))
			break;

	return;
}

bool line_to_info(char **file, t_cub3d *info)
{
	if (!file)
		return (cbd_error(ERR_MEMORY), FAILURE);
	fill_text_col(file, info);
	fill_map(file, info);

	ft_free_split(file);
	return (SUCCESS);
}
