/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:23:03 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/25 02:03:15 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**ch2str(char **src)
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

char	**str2ch(t_env **src)
{
	char	**dest;
	char	*tmp;
	size_t	i;
	size_t	j;

	dest = malloc(sizeof(char *) * (arrlen(src) + 1));
	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i]->name && src[i]->val)
		{
			tmp = ft_strjoin(src[i]->name, "=");
			dest[j] = ft_strjoin(tmp, src[i]->val);
			free(tmp);
			j++;
		}
		i++;
	}
	dest[j] = NULL;
	return (dest);
}

void	interrupt(t_env **env)
{
	write(1, "\n", 1);
	free_2d_env(env);
	exit(0);
}

void	command_list(t_env ***env, t_args *args)
{
	t_args	*cur;
	char	**tmp;

	cur = args;
	while (cur != NULL)
	{
		tmp = str2ch(*env);
		process_variables(cur, tmp);
		free_2d_array(tmp);
		execute_command(cur, env);
		cur = cur->next;
	}
}

int		main(int ac, char **av, char **env)
{
	t_args	args;
	t_env	**env_var;

	(void)ac;
	(void)av;
	g_res = 1;
	g_status = 0;
	env_var = ch2str(env);
	while (1)
	{
		signal(SIGINT, hello_sigint);
		signal(SIGQUIT, hello_sigquit);
		g_res == 0 ? 0 : hello();
		g_res = get_next_line(0, &g_line);
		if (g_res == 0 && ft_strlen(g_line) == 0)
			interrupt(env_var);
		parse_line(&args, g_line);
		free(g_line);
		command_list(&env_var, &args);
		free_args(&args);
	}
	free_2d_env(env_var);
	return (0);
}
