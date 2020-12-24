/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:19:32 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/24 15:19:35 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_last_redirect(t_args *args, t_red **last0, t_red **last1)
{
	t_red	*cur;
	int		fd;

	fd = -1;
	cur = args->red;
	while (cur != NULL)
	{
		if (cur->red == 1 || cur->red == 2)
		{
			*last1 = cur;
			fd = open(cur->file, O_CREAT | O_RDWR, 0644);
			close(fd);
		}
		else
			*last0 = cur;
		cur = cur->next;
	}
}

void	unset_redirect(t_savefd *save)
{
	if (save->last1 != NULL)
	{
		dup2(save->redir1, 1);
		close(save->redir1);
	}
	if (save->last0 != NULL)
	{
		dup2(save->redir0, 0);
		close(save->redir0);
	}
}

void	set_redirect(t_args *args, t_savefd *save)
{
	save->last0 = NULL;
	save->last1 = NULL;
	find_last_redirect(args, &(save->last0), &(save->last1));
	if (save->last1 != NULL)
	{
		save->redir1 = dup(1);
		close(1);
		if (save->last1->red == 1)
			open(save->last1->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (save->last1->red == 2)
			open(save->last1->file, O_CREAT | O_APPEND | O_RDWR, 0644);
	}
	if (save->last0 != NULL)
	{
		save->redir0 = dup(0);
		close(0);
		open(save->last0->file, O_RDONLY);
	}
}

void	execute_command(t_args *args, t_env ***env)
{
	t_savefd	save;
	int			flag;

	flag = (args->flag_in_pipe || args->flag_out_pipe) ? 1 : 0;
	args->red != NULL ? set_redirect(args, &save) : 0;
	if (args->arg[0] == NULL)
		return ;
	if (!(ft_strncmp(args->arg[0], "echo", 5)) && !flag)
		ft_echo(args->arg);
	else if (!(ft_strncmp(args->arg[0], "pwd", 4)) && !flag)
		ft_pwd();
	else if (!(ft_strncmp(args->arg[0], "cd", 3)) && !flag)
		ft_cd(args->arg, *env);
	else if (!(ft_strncmp(args->arg[0], "export", 7)) && !flag)
		*env = msh_export(*env, args->arg);
	else if (!(ft_strncmp(args->arg[0], "unset", 6)) && !flag)
		msh_unset(*env, args->arg);
	else if (!(ft_strncmp(args->arg[0], "env", 4)) && !flag)
		msh_env(*env);
	else if (!(ft_strncmp(args->arg[0], "exit", 5)) && !flag)
		ft_exit(*env, args);
	else
		ft_fork(args, *env, flag);
	args->red != NULL ? unset_redirect(&save) : 0;
}
