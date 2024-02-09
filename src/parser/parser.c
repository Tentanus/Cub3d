
#include "CBDerror.h"
#include "CBDparser.h"
#include "Cub3d.h"
#include "libft.h"

#include <unistd.h>

static char *read_fd(int fd)
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
	return (res);
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
	char *fileline;

	if (fd == -1)
		return (FAILURE);
	fileline = read_fd(fd);
	close(fd);
	if (fileline == NULL)
		return (cbd_error(ERR_MEMORY), FAILURE);

#ifdef LOG
	ft_printf("LOG:\tREAD FILE:\n%s\n\n", fileline);
#endif /* ifdef LOG                                                            \
		ft_printf("LOG:\tREAD FILE:\n%s\n\n", fileline);                       \
	*/

	ft_bzero(info, sizeof(t_cub3d));
	if (line_to_info(ft_split(fileline), info) || set_default(info))
		return (cbd_error(ERR_MEMORY), FAILURE);
	free(fileline);

#ifdef LOG
	show_info(info);
#endif /* ifdef LOG */

	return (SUCCESS);
}
