#ifndef CBD_ERROR_H
#define CBD_ERROR_H

typedef enum e_errnum
{
	SUCCESS,
	ERR_ARGUMENT,
	ERR_FILE,
	ERR_READ,
	ERR_MEMORY,
	ERR_PARSE_ID,
	_SIZE_ERRNUM

} t_errnum;

void cbd_error(t_errnum);

#endif // !CBD_ERROR_H
