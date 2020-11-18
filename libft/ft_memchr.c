/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:47:08 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/24 18:24:47 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*s1;
	unsigned char		c1;

	s1 = (unsigned char *)s;
	c1 = (unsigned char)c;
	while (n)
	{
		if (*s1 == c1)
			return ((void *)s1);
		s1++;
		n--;
	}
	return (NULL);
}
