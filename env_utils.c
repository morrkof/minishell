/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:39:01 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/25 13:09:57 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arrlen(t_env **src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i]->name && src[i]->val)
			j++;
		i++;
	}
	return (j);
}

t_env	*get_env(t_env **env, char *name)
{
	while (*env)
	{
		if ((*env)->name)
		{
			if (!(ft_strncmp((*env)->name, name, ft_strlen(name))))
				return (*env);
		}
		env++;
	}
	return (NULL);
}

void	set_env(t_env ***env, char *name, char *val)
{
	t_env	*tmp;

	if ((tmp = get_env(*env, name)) != 0)
	{
		free(tmp->val);
		tmp->val = ft_strdup(val);
	}
}
