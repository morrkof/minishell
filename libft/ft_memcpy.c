/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 10:40:19 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/25 17:59:50 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest2;
	unsigned const char	*src2;
	size_t				i;

	if (dest == src)
		return (dest);
	dest2 = dest;
	src2 = src;
	i = 0;
	while (n)
	{
		dest2[i] = src2[i];
		i++;
		n--;
	}
	return (dest);
}
