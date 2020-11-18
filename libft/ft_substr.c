/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:53:22 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/25 18:14:45 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;
	size_t	lenreal;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	lenreal = ft_strlen(s) - start;
	if (lenreal >= len)
		s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (lenreal < len)
		s1 = (char *)malloc(sizeof(char) * (lenreal + 1));
	if (!s1)
		return (NULL);
	i = 0;
	while (i < len && s[i + start] != '\0')
	{
		s1[i] = s[i + start];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
