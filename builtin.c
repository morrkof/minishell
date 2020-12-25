/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:52:36 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/25 13:33:34 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **args, t_env **env)
{
	char	*buf;

	if ((g_status = chdir(args[1]) * -1) == 1)
		print_errno_error();
	buf = getcwd(NULL, 0);
	set_env(&env, "PWD", buf);
	free(buf);
}

void	ft_pwd(void)
{
	char *buf;

	buf = getcwd(NULL, 0);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	g_status = 0;
}

void	ft_echo(char **args)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	while (args[i] != NULL && !(ft_strncmp(args[i], "-n", 3)))
	{
		flag = 1;
		i++;
	}
	while (args[i] != 0)
	{
		if (!(ft_strcmp(args[i], "$?")))
			ft_putnbr_fd(g_status, 1);
		else
			write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != 0)
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	g_status = 0;
}

int		ft_exit(t_env **env, t_args *args)
{
	if (args->arg[1] != NULL)
		g_status = ft_atoi(args->arg[1]);
	else
		g_status = 0;
	free_2d_env(env);
	free_args(args);
	exit(g_status);
}
