/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 20:26:32 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/16 00:02:42 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char *d1;
	unsigned const char *d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	while (n != 0)
	{
		if (*d1 != *d2 || *d1 == '\0' || *d2 == '\0')
			return (*d1 - *d2);
		d1++;
		d2++;
		n--;
	}
	return (0);
}
