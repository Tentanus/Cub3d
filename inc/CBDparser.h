#ifndef CBD_PARSER_H
#define CBD_PARSER_H

#include "get_next_line.h"

#include <stdbool.h>

#define MAP_CHARACTER " 01NSWE"
// maps can only contain spaces, meaning no other whitespace
// characters;

typedef enum e_type_id
{
	TYPE_ID_NORTH,
	TYPE_ID_SOUTH,
	TYPE_ID_WEST,
	TYPE_ID_EAST,
	TYPE_ID_CEILING,
	TYPE_ID_FLOOR,
	TYPE_ID_MAX
} t_type_id;

typedef struct s_cub3d t_cub3d;

int parser(int fd, t_cub3d *info);
bool line_to_info(char **file, t_cub3d *info);

#endif // !CBD_PARSER_H
