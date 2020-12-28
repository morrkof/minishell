/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synth_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:09:16 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/28 22:09:31 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_args(t_args *args)
{
	t_red	*red;

	while (args != NULL)
	{
		if (args->arg[0] == NULL && args->next != NULL)
			return (0);
		red = args->red;
		while (red != NULL)
		{
			if (red != NULL && red->file[0] == '\0')
				return (0);
			red = red->next;
		}
		args = args->next;
	}
	return (1);
}

