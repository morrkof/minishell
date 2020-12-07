/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:42:50 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/06 22:43:31 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_env(t_env **env)
{
	int		i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (env[i]->name == NULL)
		{	
			//puts("NULL!");
			continue;
		}
		write(1, env[i]->name, ft_strlen(env[i]->name));
		write(1, "=", 1);
		write(1, env[i]->val, ft_strlen(env[i]->val));
		write(1, "\n", 1);
	}
}

void	msh_unset(t_env **env, char **arr)
{
	int		i;
	char	*s;
	size_t	len;

	s = arr[1];
	i = -1;
	while (env[++i] != NULL)
	{
		if (env[i]->name == NULL)
			continue;
		len = ft_strlen(s) > ft_strlen(env[i]->name) ? ft_strlen(s) :
			ft_strlen(env[i]->name);
		int res = ft_strncmp(s, env[i]->name, len);
		if (res == 0)
		{
			free(env[i]->name);
			env[i]->name = NULL;
			free(env[i]->val);
			env[i]->val = NULL;
			break;
		}
	}
}
