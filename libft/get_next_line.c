/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 14:49:29 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/21 13:49:02 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin2(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	free(s1);
	s1 = NULL;
	return (result);
}

int			get_next_line(int fd, char **line)
{
	char	*buf;
	int		result;

	result = 1;
	if (!line)
		return (0);
	buf = malloc(2);
	*line = malloc(1);
	**line = '\0';
	*buf = '\0';
	while (*buf != '\n' && result)
	{
		result = read(fd, buf, 1);
		buf[1] = '\0';
		if (*buf != '\n' && result)
			*line = ft_strjoin2(*line, buf);
	}
	free(buf);
	return (result);
}
