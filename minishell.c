/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:23:03 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/17 13:13:46 by ppipes           ###   ########.fr       */
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

void	hello()
{
	char	*pwd;

	write(1, "msh:", 4);
	pwd = getcwd(NULL, 0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "$ ", 2);
	free(pwd);
}

void	hello_sigquit()
{
	write(1, "\b\b  \b\b", 6);
	SIG_IGN;
}

void	hello_sigint()
{
	write(1, "\n", 1);
	SIG_IGN;
	g_res = 0;
	free(g_line);
	g_line = ft_strdup(" ");
	hello();
}

t_env	**init_exit_status(t_env **src)
{
	t_env	*tmp;
	t_env	**copy;
	int		i;

	i = 0;
	tmp = malloc(sizeof(t_env));
	tmp->name = ft_strdup("?");
	tmp->val = ft_strdup("0");
	while (src[i] != NULL)
		i++;
	copy = malloc(sizeof(t_env *) * (i + 2));
	copy = copy_env(copy, src);
	copy[i] = tmp;
	copy[i + 1] = NULL;
	free(src);
	return (copy);
}

int		main(int ac, char **av, char **env)
{
	t_args	args;
	t_args	*cur;
	t_env	**env_var;
	char	*pwd;

	(void)ac;
	(void)av;
	g_res = 1;
	env_var = NULL;
	env_var = init_exit_status(char_to_struct(env));
	while (1)
	{
		signal(SIGINT, hello_sigint);
		signal(SIGQUIT, hello_sigquit);
		g_res == 0 ? 0 : hello();
		g_res = get_next_line(0, &g_line);
		if (g_res == 0 && ft_strlen(g_line) == 0)
		{
			write(1, "\n", 1);
			exit(0);
		}
		else if (g_res == 0 && ft_strlen(g_line) != 0)
			continue;
		parse_line(&args, g_line);
		cur = &args;
		while (cur != NULL)
		{
			process_variables(cur, struct_to_char(env_var));
			execute_command(cur, &env_var);
			cur = cur->next;
		}
		free(g_line);
	}
	return (0);
}
