/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_alph_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:00:18 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/25 13:11:17 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**copy_env_ptrs(t_env **dest, t_env **src)
{
	int	i;

	i = -1;
	while (src[++i] != NULL)
	{
		dest[i] = src[i];
	}
	dest[i] = NULL;
	return (dest);
}

int		more(t_env *lhs, t_env *rhs)
{
	if (lhs->name == NULL || rhs == NULL)
	{
		return (1);
	}
	if (ft_strcmp(lhs->name, rhs->name) > 0)
		return (1);
	else
		return (0);
}

void	swap(t_env **a, t_env **b)
{
	t_env	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void	sort(t_env **env)
{
	int		i;
	int		j;
	int		size;

	size = 0;
	while (env[size] != NULL)
		size++;
	i = size;
	while (i > 0)
	{
		j = -1;
		while (++j < i - 1)
		{
			if (env[j]->name == NULL || env[j + 1]->name == NULL ||
				more(env[j], env[j + 1]))
				swap(&env[j], &env[j + 1]);
		}
		i--;
	}
}

void	env_alph_order(t_env **env)
{
	t_env	**copy;
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	copy = malloc(sizeof(t_env *) * (i + 1));
	if (copy == NULL)
		return ;
	copy = copy_env_ptrs(copy, env);
	sort(copy);
	i = -1;
	while (copy[++i] != NULL)
	{
		if (copy[i]->name == NULL)
		{
			continue;
		}
		write(1, "declare -x ", 11);
		write(1, copy[i]->name, ft_strlen(copy[i]->name));
		write(1, "=", 1);
		write(1, copy[i]->val, ft_strlen(copy[i]->val));
		write(1, "\n", 1);
	}
	free(copy);
}
