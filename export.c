/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 22:42:08 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/29 02:02:02 by ppipes           ###   ########.fr       */
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

	if (s == NULL)
		return (NULL);
	start = ft_strchr(s, '=') - s;
	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->name = ft_substr(s, 0, start);
	start++;
	env->val = ft_substr(s, start, ft_strlen(s) - start);
	return (env);
}

t_env	**add_var_to_list(int i, t_env **env, t_env *temp)
{
	t_env	**copy;

	copy = malloc(sizeof(t_env *) * (i + 2));
	if (copy == NULL)
		return (env);
	copy = copy_env(copy, env);
	copy[i] = temp;
	free(env);
	return (copy);
}

int		identifier_is_valid(char *s)
{
	char c;

	c = s[0];
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	write(1, "msh: export: `", 15);
	write(1, s, ft_strlen(s));
	write(1, "\': not a valid identifier\n", 26);
	return (0);
}

t_env	**msh_export(t_env **env, char **arr)
{
	int		i;
	int		j;
	t_env	*temp;

	if (check_arr(env, arr))
		return (env);
	j = 1;
	while ((temp = split_arg(arr[j])) != NULL)
	{
		if (!(ft_strlen(temp->name)) || !(ft_strlen(temp->val)))
			return (env);
		if (!(identifier_is_valid(temp->name)))
			return (env);
		if ((i = check_exist(env, temp)) == 0)
			return (env);
		env = add_var_to_list(i, env, temp);
		j++;
	}
	g_status = 0;
	return (env);
}
