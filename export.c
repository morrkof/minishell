/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 22:42:08 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/06 22:43:15 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**copy_env(t_env **dst, t_env **src)
{
	int	i;

	i = -1;
	while (src[++i] != NULL)
	{
		dst[i] = src[i];
	}
	dst[i + 1] = NULL;
	return (dst);
}

t_env	*split_arg(char *s)
{
	t_env	*env;
	int		start;

	start = ft_strchr(s, '=') - s;
	env = malloc(sizeof(t_env));
	env->name = ft_substr(s, 0, start);
	start++;
	env->val = ft_substr(s, start, ft_strlen(s) - start);
	return env;
}

void	free_t_env(t_env *env)
{
	free(env->name);
	free(env->val);
	free(env);
}

t_env	**msh_export(t_env **env, char **arr)
{
	int		i;
	t_env	**copy;
	t_env	*temp;

	temp = split_arg(arr[1]);
	i = -1;
	while (env[++i] != NULL)
	{
/*		if (env[i]->name == NULL)
		{
			env[i]->name = temp->name;
			env[i]->val = temp->val;
			free_t_env(temp);
			return (env);
		}
*/	}
	copy = malloc(sizeof(t_env *) * (i + 2));
	copy = copy_env(copy, env);

	copy[i] = temp;
	free(env);
	return (copy);
}

