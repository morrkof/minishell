/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <student.21-school.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:54:56 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/26 13:58:49 by ppipes           ###   ########.fr       */
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

void    ft_cd(char **args)
{
    chdir(args[0]);
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

    pid = fork();
    if (pid == 0) // это дочка
	{
		if (execve(args[0], args, envp) == -1)
		{
			perror ("lsh");
			exit (-1);
		}
	}
	else if (pid < 0) // это ошибка
			perror ("lsh");
	else // это родитель
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

void	execute_command(char *line, char **envp)
{
	char *args[] = {"..", "Blablabla", "ololo", NULL};
	// char *arg2 = "..";
	// char *arg3 = "$PATH";
	int flag_n = 0;

	if (!(ft_strncmp(line, "echo", 4)))
		ft_echo(args, flag_n);
	else if (!(ft_strncmp(line, "pwd", 3)))
		ft_pwd();
	else if (!(ft_strncmp(line, "cd", 2)))
		ft_cd(args);
	else if (!(ft_strncmp(line, "export", 6)))
		printf("check export\n");
	else if (!(ft_strncmp(line, "unset", 5)))
		printf("check unset\n");
	else if (!(ft_strncmp(line, "env", 3)))
		printf("check env\n");
	else if (!(ft_strncmp(line, "exit", 4)))
		exit(0);
	else
		ft_fork(args, envp);
}