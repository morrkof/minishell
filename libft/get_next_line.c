/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 14:49:29 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/25 14:30:21 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*write_tail(char **line, char *buf, int *is_tail)
{
	char	*head;
	char	*dest;

	if (!(head = write_head(buf)))
	{
		free(*line);
		*line = NULL;
		free(buf);
		return (NULL);
	}
	if (!(*line = gnl_strjoin(*line, head)))
	{
		free(buf);
		return (NULL);
	}
	free(head);
	if (!(dest = gnl_strdup(buf)))
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	*is_tail = 1;
	return (dest);
}

char	*write_head(char *buf)
{
	size_t	i;
	char	*head;
	size_t	lenbuf;

	i = 0;
	lenbuf = gnl_strlen(buf, '\n');
	if (!(head = malloc(sizeof(char) * (lenbuf + 1))))
		return (NULL);
	while (i < lenbuf)
	{
		head[i] = buf[i];
		i++;
	}
	head[i] = '\0';
	return (head);
}

int		read_buf(int fd, int *result, char **line, char **buf)
{
	if (!(*buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	if ((*result = read(fd, *buf, BUFFER_SIZE)) == -1)
	{
		free(*line);
		*line = NULL;
		free(*buf);
		return (0);
	}
	*(*buf + *result) = '\0';
	while (!(gnl_strchr(*buf, '\n')) && *result > 0)
	{
		if (!(*line = gnl_strjoin(*line, *buf)))
			return (0);
		if (!(*result = read(fd, *buf, BUFFER_SIZE)))
			return (1);
		*(*buf + *result) = '\0';
	}
	return (2);
}

int		process_tail(char **line, char **tail, int *is_tail)
{
	if (gnl_strchr(*tail, '\n'))
	{
		if (!(*tail = write_tail(line, *tail, is_tail)))
			return (0);
		return (1);
	}
	if (!(*line = gnl_strjoin(*line, *tail)))
		return (0);
	free(*tail);
	*is_tail = 0;
	return (2);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*tail;
	static int	is_tail;
	int			result;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || !(*line = malloc(sizeof(char))))
		return (-1);
	**line = '\0';
	if (is_tail)
	{
		if (!(result = process_tail(line, &tail, &is_tail)))
			return (-1);
		if (result == 1)
			return (1);
	}
	if (!(read_buf(fd, &result, line, &buf)))
		return (-1);
	if (gnl_strchr(buf, '\n') && !(tail = write_tail(line, buf, &is_tail)))
		return (-1);
	if (!result)
	{
		free(buf);
		return (0);
	}
	return (1);
}
