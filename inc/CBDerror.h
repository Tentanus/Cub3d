/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CBDerror.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweverli <mweverli@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:30:03 by mweverli          #+#    #+#             */
/*   Updated: 2024/02/13 19:30:13 by mweverli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBDERROR_H
# define CBDERROR_H

typedef enum e_errnum
{
	SUCCESS,
	ERR_ARGUMENT,
	ERR_FILE,
	ERR_READ,
	ERR_MEMORY,
	ERR_PARSE_ID,
	ERR_PARSE_FORMAT,
	ERR_PARSE_RGB,
	ERR_PARSE_PATH,
	ERR_PARSE_FILLED,
	_SIZE_ERRNUM
}	t_errnum;

void	cbd_error(t_errnum id);

#endif // !CBDERROR_H
