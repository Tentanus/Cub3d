
#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"

#include "libft.h"
#include <sys/types.h>

static const char *g_id_str[TYPE_ID_MAX] = {
	[TYPE_ID_NORTH] = "NO", [TYPE_ID_SOUTH] = "SO", [TYPE_ID_WEST] = "WE",
	[TYPE_ID_EAST] = "EA",	[TYPE_ID_FLOOR] = "F",	[TYPE_ID_CEILING] = "C"};

uint32_t get_colour(char *str, bool *err)
{
	(void)str;
	(void)err;
	//	size_t start;
	//
	//	start = ft_strskipis(str, ft_isspace);
	return (1);
}

char *get_texture(char *str, bool *err)
{
	size_t start;
	size_t end;
	char *ret;

	start = ft_strskipis(str, ft_isspace);
	end	  = ft_strskipis(&str[start], ft_ispath);
	ret	  = ft_substr(str, start, end - start);
	if (!ret)
		*err = true;
	printf("| %s\n", ret);
	return (ret);
}

bool set_infovalue(t_cub3d *info, t_type_id id, char *str)
{
	bool err;

	err = false;
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
	return (err);
}

t_type_id get_identifier(char *str)
{
	ssize_t idx;
	ssize_t id_idx;

	idx	   = ft_strskipis(str, ft_isspace);
	id_idx = TYPE_ID_NORTH;
	while (id_idx != TYPE_ID_MAX)
	{
		if (!ft_strncmp(&str[idx], g_id_str[id_idx],
						ft_strlen(g_id_str[id_idx])))
			break;
		id_idx++;
	}
	if (id_idx != TYPE_ID_MAX && !ft_isspace(str[ft_strlen(g_id_str[id_idx])]))
		return (TYPE_ID_MAX);
	return (id_idx);
}

bool get_data(t_cub3d *info, char **lines, ssize_t *idx)
{
	ssize_t line_idx;
	t_type_id id;

	line_idx = 0;
	(void)(info);
	while (lines[*idx])
	{
		id = get_identifier(lines[*idx]);
		if (id == TYPE_ID_MAX)
			return (cbd_error(ERR_PARSE_ID), FAILURE);
		line_idx =
			ft_strskipis(lines[*idx], ft_isspace) + ft_strlen(g_id_str[id]);
		if (!set_infovalue(info, id, &lines[*idx][line_idx]))
			return (FAILURE);

#ifdef LOG
		printf("%zu\t| %s\n\t| %s\n", *idx, lines[*idx],
			   &lines[*idx][line_idx]);
#endif // ifdef LOG
		(*idx)++;
	}
	return (SUCCESS);
}
