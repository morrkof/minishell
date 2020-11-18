/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:54:55 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/25 18:09:40 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_zero_result(void)
{
	char *s;

	s = (char *)malloc(sizeof(char));
	if (s == NULL)
		return (NULL);
	*s = '\0';
	return (s);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	start;
	size_t	finish;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	if (ft_strlen(s1) == 0)
		return (ft_zero_result());
	finish = ft_strlen(s1) - 1;
	i = 0;
	while (ft_strchr(set, s1[start]) != NULL && *s1 != '\0')
		start++;
	while (ft_strchr(set, s1[finish]) != NULL && finish > 0)
		finish--;
	if (finish < start)
		return (ft_zero_result());
	if (!(s2 = (char *)malloc(sizeof(char) * (finish - start + 2))))
		return (NULL);
	while (start <= finish)
		s2[i++] = s1[start++];
	s2[i] = '\0';
	return (s2);
}
