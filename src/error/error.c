
#include "CBDerror.h"
#include "libft.h"

static const char *g_err_msg[] = {[SUCCESS] = "-",
								  [ERR_ARGUMENT] = "give 1 argument",
								  [ERR_SUFFIX] = "argument ends with *.cub",
								  [ERR_FILE] = "unable to open file",
								  [ERR_MEMORY] = "unable to allocate memory",
								  [_SIZE_ERRNUM] = "END ERROR MESSAGES"};

void cbdError(t_errnum errnum)
{
	if (errnum == SUCCESS)
		return;
	ft_putstr_fd("Cub3d: ", STDERR_FILENO);
	ft_putendl_fd(g_err_msg[errnum], STDERR_FILENO);
}
