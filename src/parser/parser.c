#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"

char *read_fd(int fd)
{
	char *res;
	char *line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_stris(line, ft_isspace))
		{
			free(line);
			continue;
		}
		res = ft_strjoin_fs1(res, line);
		free(line);
		line = get_next_line(fd);
	}
	return (res);
}

void line_to_info(char *line, t_cub3d *info)
{
	(void)line;
	(void)info;
}

void set_default(t_cub3d *info)
{
	ft_bzero(info, sizeof(t_cub3d));
}

int parser(int fd, t_cub3d *info)
{
	char *fileline;

	if (fd == -1)
		return (FAILURE);
	fileline = read_fd(fd);
	close(fd);
	if (fileline == NULL)
		return (cbd_error(ERR_MEMORY), FAILURE);
	set_default(info);
	line_to_info(fileline, info);

	return (SUCCESS);
}
