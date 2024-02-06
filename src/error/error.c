
#include "Cub3d_error.h"

#include <unistd.h>

void cbderror(int errnum)
{
	if (errnum == SUCCESS)
		return;
	write(STDOUT_FILENO, "Cub3d: ", 7);
}
