/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:54:56 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/02 17:34:29 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit()
{
	return (0);
}

void	ft_echo(char **args)
{
	int i;
	int flag;

	flag = 0;
	i = 1;
	if(!(ft_strncmp(args[1], "-n", 2)))
	{
		flag = 1;
		i = 2;
	}
	while (args[i] != 0)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != 0)
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}

void    ft_cd(char **args)
{
    chdir(args[1]);
}

void	ft_pwd()
{
	char *buf;

	buf = getcwd(NULL, 0);
	write (1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
}

void    ft_fork(char **args, char **envp)
{
    pid_t pid;
    pid_t wpid;
    int status;

    (void)wpid;
	pid = fork();
    if (pid == 0) // это дочка
	{
		if (execve(args[0], args, envp) == -1)
		{
			perror ("error");
			exit (-1);
		}
	}
	else if (pid < 0) // это ошибка
			perror ("errorg");
	else // это родитель
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

void	execute_command(t_args *args, char **envp)
{
	char *line;
	line = args->arg[0];
	// char *arg2 = "..";
	// char *arg3 = "$PATH";

	if (!(ft_strncmp(line, "echo", 4)))
		ft_echo(args->arg);
	else if (!(ft_strncmp(line, "pwd", 3)))
		ft_pwd();
	else if (!(ft_strncmp(line, "cd", 2)))
		ft_cd(args->arg);
	else if (!(ft_strncmp(line, "export", 6)))
		printf("check export\n");
	else if (!(ft_strncmp(line, "unset", 5)))
		printf("check unset\n");
	else if (!(ft_strncmp(line, "env", 3)))
		printf("check env\n");
	else if (!(ft_strncmp(line, "exit", 4)))
		exit(0);
	else
		ft_fork(args->arg, envp);
}