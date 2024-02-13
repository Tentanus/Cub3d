
#include "Cub3d.h"
#include "libft.h"
#include <unistd.h>

static void print_map(char **map)
{
	size_t i = 0;

	if (!map)
		ft_printf("| NO MAP: \n|\n");
	else
	{
		ft_printf("| MAP: \n|\n");
		while (map[i])
		{
			ft_putendl_fd(map[i], STDOUT_FILENO);
			ft_printf("|\t%u\t|\t%s\n", i, map[i]);
			i++;
		}
	}
}

void show_info(t_cub3d *info)
{
	ft_printf("\t-=- PRINTING INFO -=-\n\n");
	if (info == NULL)
	{
		ft_putendl_fd("\n -=- NO INFO FOUND -=-\n", STDERR_FILENO);
		return;
	}

	print_map(info->map);

	ft_printf("| TEXTURE & COLLOUR: \n|\n");
	ft_printf("|\tTEXTURE  NORTH:  \t%s\n", info->text_no);
	ft_printf("|\tTEXTURE  SOUTH:  \t%s\n", info->text_so);
	ft_printf("|\tTEXTURE  WEST:   \t%s\n", info->text_we);
	ft_printf("|\tTEXTURE  EAST:   \t%s\n", info->text_ea);
	ft_printf("|\tCOLOUR   FLOOR:  \t%X\t%b\n", info->col_fl);
	ft_printf("|\tCOLOUR   CEILING:\t%X\t%b\n", info->col_ce);

	ft_printf("\n\t-=- FINISHED -=-\n\n");
}
