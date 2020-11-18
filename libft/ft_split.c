/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:35 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/25 18:04:21 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		if (s[j] != c && (s[j + 1] == c || s[j + 1] == '\0'))
			i++;
		j++;
	}
	return (i);
}

static void		ft_free(char **dst)
{
	int i;

	i = 0;
	while (dst[i] != NULL)
		free(dst[i++]);
	free(dst);
}

static char		*ft_subp(char const *s, size_t *beg, size_t len, char **dst)
{
	char	*s1;
	size_t	i;

	if (!(s1 = (char *)malloc(sizeof(char) * (len + 1))))
	{
		ft_free(dst);
		return (NULL);
	}
	i = 0;
	while (i < len && s[i + *beg] != '\0')
	{
		s1[i] = s[i + *beg];
		i++;
	}
	s1[i] = '\0';
	*beg = *beg + i;
	return (s1);
}

char			**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	beg;
	size_t	end;
	size_t	ptr;

	beg = 0;
	end = 0;
	ptr = 0;
	if (s == NULL)
		return (NULL);
	if (!(dst = (char **)malloc((ft_words(s, c) + 1) * sizeof(char*))))
		return (NULL);
	while (s[end] != '\0')
	{
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == '\0'))
		{
			while (s[beg] == c && s[beg] != '\0')
				beg++;
			if (!(dst[ptr++] = ft_subp(s, &beg, (end - beg + 1), dst)))
				return (NULL);
		}
		end++;
	}
	dst[ptr] = NULL;
	return (dst);
}
