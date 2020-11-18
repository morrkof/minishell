/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:33:05 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/25 17:47:04 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dest2;
	unsigned const char	*src2;
	size_t				i;
	unsigned char		c2;

	dest2 = dest;
	src2 = src;
	c2 = c;
	i = 0;
	while (n)
	{
		if (src2[i] == c2)
		{
			dest2[i] = src2[i];
			return (dest2 + i + 1);
		}
		dest2[i] = src2[i];
		i++;
		n--;
	}
	return (NULL);
}
