/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 20:04:37 by mweverli      #+#    #+#                 */
/*   Updated: 2022/05/16 15:56:40 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_char(char *buf, char c);
static char		*buf_2_line(char *buf, char *line);
static void		buf_update(char *buf);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			read_ret;

	if (fd < 0 || fd > OPEN_MAX || read(fd, buf, 0) == -1)
		return (NULL);
	line = ft_calloc(sizeof(char), 1);
	if (*buf)
		line = buf_2_line(buf, line);
	while (line && !(check_char(line, '\n')))
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret == -1)
			return (free(line), NULL);
		buf[read_ret] = '\0';
		line = buf_2_line(buf, line);
		if (read_ret < BUFFER_SIZE)
			break ;
	}
	buf_update(buf);
	if (read_ret == 0 && *line == '\0')
		return (free(line), NULL);
	return (line);
}

static int	check_char(char *buf, char c)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	if (c == '\n')
	{
		while (buf[i])
		{
			if (buf[i] == '\n')
				return (i + 1);
			i++;
		}
		return (0);
	}
	else
		while (buf[i])
			i++;
	return (i);
}

static char	*buf_2_line(char *buf, char *line)
{
	int		line_len;
	int		buf_len;
	char	*tmp;

	buf_len = check_char(buf, '\n');
	if (buf_len == 0)
		buf_len = check_char(buf, '\0');
	line_len = check_char(line, '\0');
	tmp = ft_calloc(sizeof(char), (line_len + buf_len + 1));
	if (!tmp)
		return (free(line), NULL);
	tmp[line_len + buf_len] = '\0';
	while (buf_len > 0)
	{
		buf_len--;
		tmp[line_len + buf_len] = buf[buf_len];
	}
	while (line_len > 0)
	{
		line_len--;
		tmp[line_len] = line[line_len];
	}
	free(line);
	return (tmp);
}

static void	buf_update(char *buf)
{
	int	nl_plus;
	int	buf_end;
	int	i;

	nl_plus = check_char(buf, '\n');
	if (nl_plus == 0)
	{
		buf[0] = '\0';
		return ;
	}
	buf_end = check_char(buf, '\0');
	i = 0;
	while (i <= (buf_end - nl_plus))
	{
		buf[i] = buf[nl_plus + i];
		i++;
	}
	buf[i] = '\0';
	return ;
}
