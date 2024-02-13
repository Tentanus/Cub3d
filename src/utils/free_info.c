
#include "Cub3d.h"
#include "libft.h"

void cbd_free_info(t_cub3d *info)
{
	if (info->map)
		ft_split_free(info->map);
	if (info->text_no)
		free(info->text_no);
	if (info->text_so)
		free(info->text_so);
	if (info->text_we)
		free(info->text_we);
	if (info->text_ea)
		free(info->text_ea);
}
