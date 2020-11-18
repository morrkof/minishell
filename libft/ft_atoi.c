/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:44:32 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 01:05:12 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_skip_start(const char *nptr, int *minus)
{
	int i;

	i = 0;
	while (nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == '\f' || \
	nptr[i] == '\v' || nptr[i] == '\t' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*minus = -1;
		i++;
	}
	return (i);
}

int			ft_atoi(const char *nptr)
{
	int				i;
	int				minus;
	unsigned long	result;

	minus = 1;
	result = 0;
	i = ft_skip_start(nptr, &minus);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (!(ft_isdigit(nptr[i + 1])))
		{
			if (result > LONG_MAX - 1 && minus == -1)
				return (0);
			if (result > LONG_MAX && minus == 1)
				return (-1);
			return (result * minus);
		}
		i++;
	}
	return (0);
}
