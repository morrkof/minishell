/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:45:41 by miphigen          #+#    #+#             */
/*   Updated: 2020/11/23 12:54:28 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*red_init()
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (red != NULL)
	{
		red->red = 0;
		red->file = NULL;
		red->next = NULL;
		red->prev = NULL;
	}
	return (red);
}

void	add_redirect(char *s, t_args *args)
{
	char	*tmp;
	t_red	*red;

	if (args->red == NULL)
		args->red = red_init();
	red = args->red;
	while (red->next != NULL)
		red = red->next;
	red->next = red_init();
	red->next->prev = red;
	red = red->next;
	if (*s == '<' && *(s + 1) == '<')
		red->red = 4;
	else if (*s == '<')
		red->red = 3;
	else if (*s == '>' && *(s + 1) == '>')
		red->red = 2;
	else if (*s == '>')
		red->red = 1;
	tmp = ft_strtrim(s, ">< ");
	printf("%s --> %s\n", s, tmp);
	
}
//	int				red;			// > - 1;  >> - 2; < - 3;
