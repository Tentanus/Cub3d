#ifndef CBD_PARSER_H
#define CBD_PARSER_H

#include "get_next_line.h"

typedef struct s_cub3d t_cub3d;

int parser(int fd, t_cub3d *info);

char *readfile(int fd);

#endif // !CBD_PARSER_H
