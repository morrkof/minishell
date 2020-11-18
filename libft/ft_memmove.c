/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:43:58 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/18 21:39:18 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest2;
	unsigned const char	*src2;
	size_t				i;

	dest2 = dest;
	src2 = src;
	if (src2 < dest2)
	{
		while (n)
		{
			dest2[n - 1] = src2[n - 1];
			n--;
		}
	}
	if (src2 > dest2)
	{
		i = 0;
		while (i < n)
		{
			dest2[i] = src2[i];
			i++;
		}
	}
	return (dest);
}
