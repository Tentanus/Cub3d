
#include "Cub3d.h"
#include "libft.h"
#include <unistd.h>

static void print_map(char **map)
{
	size_t i = 0;

	while (map[i])
	{
		ft_putendl_fd(map[i], STDOUT_FILENO);
		ft_printf("%d\t|\t%s\n", i, map[i]);
		i++;
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

	if (info->map != NULL)
		print_map(info->map);

	ft_printf("TEXTURE NORTH:\t%s\n", info->text_no);
	ft_printf("TEXTURE SOUTH:\t%s\n", info->text_so);
	ft_printf("TEXTURE  WEST:\t%s\n", info->text_we);
	ft_printf("TEXTURE  EAST:\t%s\n", info->text_ea);

	ft_printf("\n\t-=- FINISHED -=-\n\n");
}
