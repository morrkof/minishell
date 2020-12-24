/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:23:03 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/24 17:55:07 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**char_to_struct(char **src)
{
	t_env	**dest;
	size_t	len;
	size_t	i;
	int		eq;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	dest = malloc(sizeof(t_env *) * (len + 1));
	while (i < len)
	{
		dest[i] = malloc(sizeof(t_env));
		eq = ft_strchr(src[i], '=') - src[i];
		dest[i]->name = ft_substr(src[i], 0, eq);
		dest[i]->val = ft_substr(src[i], eq + 1, ft_strlen(src[i]) - eq);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**struct_to_char(t_env **src)
{
	char	**dest;
	char	*tmp;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	dest = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		tmp = ft_strjoin(src[i]->name, "=");
		dest[i] = ft_strjoin(tmp, src[i]->val);
		free(tmp);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int		main(int ac, char **av, char **env)
{
	t_args	args;
	t_args	*cur;
	t_env	**env_var;
	char	**tmp;

	(void)ac;
	(void)av;
	g_res = 1;
	g_status = 0;
	env_var = char_to_struct(env);
	while (1)
	{
		signal(SIGINT, hello_sigint);
		signal(SIGQUIT, hello_sigquit);
		g_res == 0 ? 0 : hello();
		g_res = get_next_line(0, &g_line);
		if (g_res == 0 && ft_strlen(g_line) == 0)
		{
			write(1, "\n", 1);
			free_2d_env(env_var);
			free(g_line);
			free_args(&args);
			exit(0);
		}
		else if (g_res == 0 && ft_strlen(g_line) != 0)
			continue;
		parse_line(&args, g_line);
		free(g_line);
		cur = &args;
		while (cur != NULL)
		{
			tmp = struct_to_char(env_var);
			process_variables(cur, tmp);
			free_2d_array(tmp);
			execute_command(cur, &env_var);
			cur = cur->next;
		}
		free_args(&args);
	}
	free_2d_env(env_var);
	return (0);
}
