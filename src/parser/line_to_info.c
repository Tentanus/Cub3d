
#include "CBDparser.h"
#include "Cub3d.h"
#include "libft.h"

static const char *g_file_id[6] = {"NO", "SO", "WE", "EA", "C", "F"};

static int identify_info(char *line)
{
	size_t str_i;
	size_t id_i;

	str_i = ft_skip_whitespace(line);
	id_i  = 0;
	while (id_i < 6)
	{
		if (!ft_strncmp(&line[str_i], g_file_id[id_i],
						ft_strlen(g_file_id[id_i])))
			return (id_i);
		id_i++;
	}
	if (ft_)
		return ();
}

static void transfer_info(file, &i, info)
{
}

bool line_to_info(char **file, t_cub3d *info)
{
	size_t i;
	size_t func_id;

	i = 0;
	if (!file)
		return (FAILURE);

	while (file[i])
	{
		func_id = identify_info(file[i]);
		transfer_info(file, &i, info);
	}

	ft_free_split(file);
	return (SUCCESS);
}
