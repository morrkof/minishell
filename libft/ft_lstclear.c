/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 19:45:26 by ppipes            #+#    #+#             */
/*   Updated: 2020/05/21 00:19:52 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *nxt;
	t_list *cur;

	cur = *lst;
	while (cur != NULL)
	{
		nxt = cur->next;
		ft_lstdelone(cur, del);
		cur = nxt;
	}
	*lst = NULL;
}
