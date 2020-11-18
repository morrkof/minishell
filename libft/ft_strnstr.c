/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 20:25:42 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/22 18:01:44 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t find;
	size_t littlelen;
	size_t j;

	i = 0;
	if (little[i] == '\0' || little == NULL)
		return ((char *)big);
	littlelen = ft_strlen(little);
	while (i < len && big[i] != '\0')
	{
		find = 0;
		j = i;
		while (big[j] == little[find] && big[j] != '\0' && j < len)
		{
			if (find == littlelen - 1)
				return ((char *)big + j - find);
			j++;
			find++;
		}
		i++;
	}
	return (NULL);
}
