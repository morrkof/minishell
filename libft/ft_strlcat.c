/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 20:01:11 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/15 22:11:28 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	if (size < j)
		return (size + ft_strlen(src));
	while (i + 1 + j < size && src[i] != '\0')
	{
		dst[j + i] = src[i];
		i++;
	}
	if (size > 0)
		dst[j + i] = '\0';
	return (ft_strlen(src) + j);
}
