#ifndef CUB3D_ERROR_H
#define CUB3D_ERROR_H

typedef enum e_errno
{
	SUCCESS,
	ERR_ARGUMENT,
	ERR_SUFFIX

} t_errno;

void cbderror(int);

#endif // !CUB3D_ERROR_H
