
#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"
#include "libft.h"

#include <unistd.h>

static char **read_fd(int fd)
{
	char *res;
	char *line;

	res	 = ft_calloc(1, sizeof(char));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!ft_stris(line, ft_isspace))
			res = ft_strjoin_fs1(res, line);
		free(line);
		line = get_next_line(fd);
	}

#ifdef LOG
	ft_printf("LOG:\tREAD FILE:\n%s\n\n", res);
#endif // ifdef LOG

	return (ft_split(res, '\n'));
}

static bool set_default(t_cub3d *info)
{
	if (!info->text_no)
		info->text_no = ft_strdup(DEF_TEXT_NO);
	if (!info->text_so)
		info->text_so = ft_strdup(DEF_TEXT_SO);
	if (!info->text_we)
		info->text_we = ft_strdup(DEF_TEXT_WE);
	if (!info->text_ea)
		info->text_ea = ft_strdup(DEF_TEXT_EA);
	if (!info->text_no || !info->text_so || !info->text_we || !info->text_ea)
		return (FAILURE);

	return (SUCCESS);
}

int parser(int fd, t_cub3d *info)
{
	char **filelines;
	ssize_t idx;

	idx = 0;
	if (fd == -1)
		return (FAILURE);
	filelines = read_fd(fd);
	close(fd);
	if (filelines == NULL)
		return (cbd_error(ERR_MEMORY), FAILURE);

	ft_bzero(info, sizeof(t_cub3d));
	if (!get_data(info, filelines, &idx))
		return (FAILURE);
	if (!get_map(info, filelines, &idx))
		return (FAILURE);
	set_default(info); // this is a temporary fucntion;

#ifdef LOG
	show_info(info);
#endif /* ifdef LOG */

	return (SUCCESS);
}
