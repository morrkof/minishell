/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:42:50 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/16 20:36:02 by ppipes           ###   ########.fr       */
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
	set_env(env, "?", "0");
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
	set_env(env, "?", "0");
}
