#ifndef CBD_ERROR_H
#define CBD_ERROR_H

typedef enum e_errnum
{
	SUCCESS,
	ERR_ARGUMENT,
	ERR_SUFFIX,
	ERR_FILE,
	ERR_MEMORY,
	_SIZE_ERRNUM

} t_errnum;

void cbdError(t_errnum);

#endif // !CBD_ERROR_H
