/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:58:31 by miphigen          #+#    #+#             */
/*   Updated: 2020/11/15 20:01:53 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char ch)
{
	unsigned char c;

	c = (unsigned char)ch;
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\f' ||
			c == '\v')
		return (c);
	else
		return (0);
}
