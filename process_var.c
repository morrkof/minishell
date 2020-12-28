/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:37:44 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/28 22:06:16 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *str, t_env **env)
{
	int		i;
	char	*s;

	s = malloc(100);
	i = -1;
	while (str[++i] != '\0' && str[i] != '$')
		s[i] = str[i];
	i = -1;
	while (env[++i] != NULL)
	{
		if (env[i]->name != NULL && ft_strcmp(env[i]->name, s) == 0)
			return (env[i]->val);
	}
	free(s);
	return (NULL);
}

int		get_length(char *s, int i)
{
	int j;

	j = i + 1;
	while (s[j] != '\0' && s[j] != '$')
		j++;
	return (j - i);
}

char	*replace_var(char *s, int i, t_env **env)
{
	char	*s2;
	char	*ret_value;
	int		s2_length;
	int		name_length;

	s2 = get_value(&s[i + 1], env);
	if (s2 == NULL)
		s2 = "";
	name_length = get_length(s + 1, i);
	s2_length = ft_strlen(s2);
	ret_value = malloc(ft_strlen(s2) + ft_strlen(s) + 1);
	ft_memcpy(ret_value, s, i);
	ft_memcpy(&ret_value[i], s2, s2_length);
	ret_value[i + s2_length] = '\0';
	ft_strlcat(ret_value, &s[i + name_length + 1], ft_strlen(ret_value) +
		ft_strlen(&s[i + name_length]));
	free(s);
	return (ret_value);
}

char	*replace_all_variables(char *s, t_env **env)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '$')
		{
			s = replace_var(s, i, env);
			i = 0;
		}
	}
	return (s);
}

void	process_variables(t_args *args, t_env **env)
{
	char	**arr;
	int		i;

	arr = args->arg;
	if (args->sq_flag != 0)
		return ;
	i = -1;
	while (arr[++i] != NULL)
		arr[i] = replace_all_variables(arr[i], env);
}
