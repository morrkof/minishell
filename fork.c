/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:01:21 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/23 18:04:19 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_fork(t_args *arg, t_env **env, int flag)
{
	pid_t	pid;
	t_pipe	pipes;
	int		status;
	char	*path;

	if (flag)
		set_pipes(arg, &pipes);
	if ((path = find_exec_path(arg, env)) == NULL)
		return (-1);
	pid = fork();
	if (pid == 0 && (execve(path, arg->arg, struct_to_char(env)) == -1))
		print_errno_error();
	else if (pid < 0)
		print_errno_error();
	else
	{
		while (waitpid(pid, &status, WUNTRACED) != 0)
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break ;
		g_status = WEXITSTATUS(status);
	}
	if (flag)
		unset_pipes(arg, &pipes);
	return (0);
}

char	*find_exec_path(t_args *arg, t_env **env)
{
	t_env	*path;
	char	*abs_path;
	char	*tmp;
	char	*exec_path;

	if (!(ft_strchr(arg->arg[0], '/')))
	{
		if ((path = get_env(env, "PATH")) != NULL)
			abs_path = get_path(arg->arg[0], split_paths(path->val));
		if (path == NULL || abs_path == NULL)
		{
			write(2, arg->arg[0], ft_strlen(arg->arg[0]));
			write(2, ": command not found\n", 21);
			g_status = 127;
			return (NULL);
		}
		tmp = ft_strjoin(abs_path, "/");
		free(abs_path);
		exec_path = ft_strjoin(tmp, arg->arg[0]);
		free(tmp);
		return (exec_path);
	}
	else
		return (arg->arg[0]);
}

void	set_pipes(t_args *arg, t_pipe *pipes)
{
	static int saved;

	if (arg->flag_in_pipe)
	{
		pipes->savefd0 = dup(0);
		dup2(saved, 0);
		close(saved);
	}
	if (arg->flag_out_pipe)
	{
		pipe(pipes->pipefd);
		pipes->savefd1 = dup(1);
		saved = pipes->pipefd[0];
		dup2(pipes->pipefd[1], 1);
		close(pipes->pipefd[1]);
	}
}

void	unset_pipes(t_args *arg, t_pipe *pipes)
{
	if (arg->flag_in_pipe)
	{
		dup2(pipes->savefd0, 0);
		close(pipes->savefd0);
	}
	if (arg->flag_out_pipe)
	{
		dup2(pipes->savefd1, 1);
		close(pipes->savefd1);
	}
}

void	print_errno_error(void)
{
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}
