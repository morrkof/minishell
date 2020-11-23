/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:54:56 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/23 18:26:36 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit()
{
	return (0);
}

void	ft_echo(char **args, int flag)
{
	int i;

	i = 0;
	while (args[i] != 0)
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}

void	ft_pwd()
{
	char *buf;

	buf = getcwd(NULL, 0);
	write (1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
}

void	execute_command(char *line)
{
	char *args[] = {"Hello, world!", "Blablabla", "ololo", NULL};
	// char *arg2 = "..";
	// char *arg3 = "$PATH";
	int flag_n = 0;

	if (!(ft_strncmp(line, "echo", 4)))
		ft_echo(args, flag_n);
	else if (!(ft_strncmp(line, "pwd", 3)))
		ft_pwd();
	else if (!(ft_strncmp(line, "cd", 2)))
		printf("check cd\n");
	else if (!(ft_strncmp(line, "export", 6)))
		printf("check export\n");
	else if (!(ft_strncmp(line, "unset", 5)))
		printf("check unset\n");
	else if (!(ft_strncmp(line, "env", 3)))
		printf("check env\n");
	else if (!(ft_strncmp(line, "exit", 4)))
		exit(0);
	else
		printf("start fork\n");
}