
#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"

#include "libft.h"
#include <sys/types.h>

static const char *g_id_str[TYPE_ID_MAX] = {
	[TYPE_ID_NORTH] = "NO", [TYPE_ID_SOUTH] = "SO", [TYPE_ID_WEST] = "WE",
	[TYPE_ID_EAST] = "EA",	[TYPE_ID_FLOOR] = "F",	[TYPE_ID_CEILING] = "C"};

// clang-format off
/*
 *		char err codes;
 *			0		get_texture:	can't allocate memory [ERR_MEMORY]
 *			!		get_texture:	path isn't a 'valid' path [ERR_PARSE_PATH]
 *			 		get_texture:	after path line isn't empty [ERR_PARSE_FORMAT]
 *
 *			i		get_colour:		colour value exceeds limits [ERR_PARSE_RGB]
 *			,		get_colour:		formatting error (255,255,255) [ERR_PARSE_FORMAT]
 */
// clang-format on

void get_error(char err)
{
	if (err == '0')
		cbd_error(ERR_MEMORY);
	else if (err == '!')
		cbd_error(ERR_PARSE_PATH);
	else if (err == ' ')
		cbd_error(ERR_PARSE_FORMAT);
	else if (err == 'i')
		cbd_error(ERR_PARSE_RGB);
	else if (err == ',')
		cbd_error(ERR_PARSE_FORMAT);
}

uint32_t get_colour(char *str, char *err)
{
	size_t start;
	int i;
	int64_t val;
	uint32_t ret;

	printf("START:\t%s\n\n", str);
	start = ft_strskipis(str, ft_isspace);
	i	  = 2;
	ret	  = 0;
	ft_printf("ret:\t0000000000000000%b\t0\n", ret);
	ret = 255;
	ft_printf("ret:\t0000000000000000%b\t1\n", ret);
	ret = 0 + (255 << 8);
	ft_printf("ret:\t0000000000000000%b\t2\n", ret);
	ret = 0 + (255 << 16);
	ft_printf("ret:\t%b\t3\n", ret);
	ret = 0 + (255 << 24);
	ft_printf("ret:\t%b\t4\n\n\n", ret);

	ret = 0;
	while (i >= 0 && *err == '\0')
	{
		val = ft_atoi(&str[start]);
		if (val < 0 || val > 255)
			*err = 'i';
		ft_printf("ret:\t%b\t%i\n", ret, i);
		printf("v dc:\t%.10u\n", (uint32_t)val);
		printf("v<dc:\t%.10u\n", (uint32_t)(val << (8 * i)));
		printf("r dc:\t%.10u\n", (uint32_t)ret);
		ret += (val << (8 * i));
		printf("r +=:\t%.10u\n", (uint32_t)ret);
		ft_printf("v bi:\t%b\n", (val << (8 * i)));
		ft_printf("r bi:\t%b\t%i\n", ret, i);
		start += ft_strskipis(&str[start], ft_isdigit);
		if (i != 0 && str[start] != ',')
			*err = ',';
		start++;
		i--;
	}
	ft_printf("END:\t%b\n", ret);
	return (ret);
}

char *get_texture(char *str, char *err)
{
	size_t start;
	size_t end;
	char *ret;

	start = ft_strskipis(str, ft_isspace);
	end	  = ft_strskipis(&str[start], ft_ispath) + 1;
	ret	  = ft_substr(str, start, end - start);
	if (!ret)
		*err = '0';
	else if (!ft_stris(ret, ft_ispath))
		*err = '!';
	else if (!ft_stris(&str[end], ft_isspace))
		*err = ' ';
	return (ret);
}

bool set_infovalue(t_cub3d *info, t_type_id id, char *str)
{
	char err;

	err = '\0';
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
	get_error(err);
	return (ft_ternary(err == '\0', 1, 0));
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
		{
#ifdef LOG
			printf("%zu\t| %s\n\t| %s\n", *idx, lines[*idx],
				   &lines[*idx][line_idx]);
			return (cbd_error(ERR_PARSE_ID), FAILURE);
#endif // ifdef LOG
		}

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
