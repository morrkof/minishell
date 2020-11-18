/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:57:35 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/19 20:10:20 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_reverse(char *s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

static void	ft_negative(int *n, int *min, int *minus)
{
	if (*n == -2147483648)
	{
		*n = *n + 1;
		*min = 1;
	}
	*minus = 1;
	*n = *n * -1;
}

void		ft_putnbr_fd(int n, int fd)
{
	char	s[12];
	int		i;
	int		minus;
	int		min;

	i = 0;
	min = 0;
	minus = 0;
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n < 0)
		ft_negative(&n, &min, &minus);
	while (n > 0)
	{
		s[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	if (minus)
		s[i++] = '-';
	if (min)
		s[0] = '8';
	s[i] = '\0';
	ft_reverse(s);
	ft_putstr_fd(s, fd);
}
