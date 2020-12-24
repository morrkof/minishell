/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:44:02 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/22 00:31:21 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2d_env(t_env **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]->name);
		free(env[i]->val);
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_red(t_red *red)
{
	t_red	*cur;
	t_red	*next;

	cur = red;
	while (cur != NULL)
	{
		free(cur->file);
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	free_args(t_args *args)
{
	t_args	*cur;
	t_args	*next;

	cur = args;
	free_2d_array(cur->arg);
	free_red(cur->red);
	cur = cur->next;
	while (cur != NULL)
	{
		free_2d_array(cur->arg);
		free_red(cur->red);
		next = cur->next;
		free(cur);
		cur = next;
	}
}
