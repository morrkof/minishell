/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:37:44 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/24 16:44:58 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_value(char **env, char *var, int *size)
{
	char	*s;
	char	*variable;

	while (*env != NULL)
	{
		s = *env;
		*size = ft_strchr(s, '=') - s;
		variable = ft_substr(*env, 0, *size);
		if (ft_strncmp(var, variable, ft_strlen(var) + 1) == 0)
		{
			s = ft_substr(s, *size + 1, ft_strlen(s) - *size);
			return (s);
		}
		free(variable);
		env++;
	}
	return (NULL);
}

char	*get_value(char *s, int i, char **env, int *size)
{
	int		j;
	char	*var;
	char	*val;

	(void)env;
	j = 1;
	while (s[i + j] != '\0')
	{
		var = ft_substr(s, i + 1, j);
		val = ret_value(env, var, size);
		free(var);
		if (val != NULL)
			break ;
		j++;
	}
	return (val);
}

char	*process_var(char *s, int i, char **env)
{
	char	*s2;
	char	*ret_value;
	int		size;

	s2 = get_value(s, i, env, &size);
	if (s2 == NULL)
		return (NULL);
	ret_value = malloc(ft_strlen(s2) + ft_strlen(s) + 1);
	ft_memcpy(ret_value, s, i);
	ft_memcpy(&ret_value[i], s2, ft_strlen(s2));
	ret_value[i + ft_strlen(s2)] = '\0';
	ft_strlcat(&ret_value[i + ft_strlen(s2)], &s[i + 1 + size],
		ft_strlen(s) - i);
	free(s);
	return (ret_value);
}

void	process_variables(t_args *args, char **env)
{
	char	**arr;
	int		i;
	int		j;

	arr = args->arg;
	if (args->sq_flag != 0)
		return ;
	i = -1;
	while (arr[++i] != NULL)
	{
		j = -1;
		while (arr[i][++j] != '\0')
			if (arr[i][j] == '$' && arr[i][j + 1] != '?')
			{
				arr[i] = process_var(arr[i], j, env);
				j--;
				arr[i] = arr[i];
				if (arr[i] == NULL)
				{
					arr[i] = ft_strdup("");
					break ;
				}
			}
	}
}
