#ifndef CBD_PARSER_H
#define CBD_PARSER_H

#include "get_next_line.h"

#include <stdbool.h>

typedef struct s_cub3d t_cub3d;

int parser(int fd, t_cub3d *info);
bool line_to_info(char **file, t_cub3d *info);

#endif // !CBD_PARSER_H
