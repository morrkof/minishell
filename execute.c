/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:19:32 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/17 13:28:01 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(t_env **env, t_args *args)
{
	int status;

	if (args->arg[1] != NULL)
		status = ft_atoi(args->arg[1]);
	else
		status = 0;
	set_env(env, "?", ft_itoa(status));
	exit (status);
}

void	ft_echo(char **args, t_env **env)
{
	int i;
	int flag;

	flag = 0;
	i = 1;
	if(args[1] != NULL && !(ft_strncmp(args[1], "-n", 3)))
	{
		flag = 1;
		i = 2;
	}
	while (args[i] != 0)
	{
		// if (!(ft_strncmp(args[i], "$?", 2)))
		// 	write(1, ft_itoa(g_status), ft_strlen(ft_itoa(g_status)));
		// else
			write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != 0)
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	set_env(env, "?", "0");
}

void    ft_cd(char **args, t_env **env)
{
    if (chdir(args[1]))
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		set_env(env, "?", ft_itoa(errno));
	}
	else
	{
		set_env(env, "PWD", getcwd(NULL, 0));
		set_env(env, "?", "0");
	}
}

t_env	*get_env(t_env **env, char *name)
{
	while(*env)
	{
		if(!(ft_strncmp((*env)->name, name, ft_strlen(name))))
			return(*env);
		env++;
	}
	return (NULL);
}

int		set_env(t_env **env, char *name, char *val)
{
	t_env *tmp;

	if(tmp = get_env(env, name))
	{
		free(tmp->val);
		tmp->val = ft_strdup(val);
	}
	// else - добавить переменную
	// сделать return 
}

void	ft_pwd(t_env **env)
{
	char *buf;

	buf = getcwd(NULL, 0);
	write (1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	// g_status = 0;
	set_env(env, "?", "0");
}

char	*get_path(char *command, char *path)
{
	char **paths;
	char *pwd;
	char *tmp;
	char *path_with_cur;
	DIR *dir;
	struct dirent *ent;
	int i;

	i = 0;
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin(pwd, ":");
	free(pwd);
	path_with_cur = ft_strjoin(tmp, path);
	free(tmp);
	paths = ft_split(path_with_cur, ':');
	while(paths[i])
	{
		dir = opendir(paths[i]);
		while (ent = readdir(dir))
		{
			if (!(ft_strcmp(command, ent->d_name)))
			{
				closedir(dir);
				return(paths[i]);
			}
			// printf("%s\n", ent->d_name);
		}
		closedir(dir);
		i++;
	}
	return("errorp");
}

void    ft_fork(t_args *arg, t_env **env)
{
    pid_t pid;
    pid_t wpid;
    int status;
	static int saved;
	int pipefd[2];
	int savefd1;
	int savefd0;
	char **args = arg->arg;
	char *abs_path;
	char *tmp;
	char *exec_path;

	if (arg->flag_in_pipe)
	{
		savefd0 = dup(0);
		dup2(saved, 0);
		close(saved);
		//printf("BEFORE IN COM %s IN %d OUT %d pipefd0 %d pipefd1 %d\n",arg->arg[0], arg->flag_in_pipe,arg->flag_out_pipe,pipefd[0],pipefd[1]);
	}
	if (arg->flag_out_pipe)
	{
		pipe(pipefd);
		savefd1 = dup(1);
		saved = pipefd[0];
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		// printf("BEFORE OUT COM %s IN %d OUT %d pipefd0 %d pipefd1 %d\n",arg->arg[0], arg->flag_in_pipe,arg->flag_out_pipe,pipefd[0],pipefd[1]);
	}
	(void)wpid;
	exec_path = args[0];
	if (!(ft_strchr(args[0], '/')))
	{
		abs_path = get_path(args[0], (get_env(env, "PATH"))->val);
		tmp = ft_strjoin(abs_path, "/");
		exec_path = ft_strjoin(tmp, args[0]);
	}
	pid = fork();
    if (pid == 0) // это дочка
	{
		if (execve(exec_path, args, struct_to_char(env)) == -1)
		{
			perror ("error");
			exit (-1);
		}
	}
	else if (pid < 0) // это ошибка
			perror ("errorg");
	else // это родитель
	{
		// printf ("parent %d %d %s\n",arg->flag_in_pipe,arg->flag_out_pipe,arg->arg[0]);
		while (wpid = waitpid(pid, &status, WUNTRACED))
		{
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break ;
		}
		set_env(env, "?", ft_itoa(WEXITSTATUS(status)));
		// g_status = WEXITSTATUS(status);
	}
	if (arg->flag_in_pipe)
	{
		dup2(savefd0, 0);
		close(savefd0);
		// printf("AFTER IN COM %s IN %d OUT %d pipefd0 %d pipefd1 %d\n",arg->arg[0], arg->flag_in_pipe,arg->flag_out_pipe,pipefd[0],pipefd[1]);
	}
	if (arg->flag_out_pipe)
	{
		dup2(savefd1, 1);
		close(savefd1);
		// printf("AFTER OUT COM %s IN %d OUT %d pipefd0 %d pipefd1 %d\n",arg->arg[0], arg->flag_in_pipe,arg->flag_out_pipe,pipefd[0],pipefd[1]);
	}
}

void	set_redirect(t_args *args, t_red **last0, t_red **last1)
{
	t_red	*cur;
	int fd = -1;

	cur = args->red;
	while(cur != NULL)
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


void	execute_command(t_args *args, t_env ***env)
{
	t_red *last0; // read FROM file
	t_red *last1; // write IN file
	int	save_redir0;
	int	save_redir1;
	int fd0;
	int fd1;
	int flag = 0;
	if (args->flag_in_pipe || args->flag_out_pipe)
		flag = 1;
	if (args->red != NULL)
	{
		last0 = NULL;
		last1 = NULL;
		set_redirect(args, &last0, &last1);
		if(last1 != NULL)
		{
			save_redir1 = dup(1);
			close(1);
			if (last1->red == 1)
				fd1 = open(last1->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
			else if (last1->red == 2)
				fd1 = open(last1->file, O_CREAT | O_APPEND | O_RDWR, 0644);
		}
		if (last0 != NULL)
		{
			save_redir0 = dup(0);
			close(0);
			fd0 = open(last0->file,  O_RDONLY);
		}	
	}
	if (args->arg[0] == NULL)
		return;
	if (!(ft_strncmp(args->arg[0], "echo", 4 + 1)) && !flag)
		ft_echo(args->arg, *env);
	else if (!(ft_strncmp(args->arg[0], "pwd", 3 + 1)) && !flag)
		ft_pwd(*env);
	else if (!(ft_strncmp(args->arg[0], "cd", 2 + 1)) && !flag)
		ft_cd(args->arg, *env);
	else if (!(ft_strncmp(args->arg[0], "export", 6 + 1)) && !flag)
		*env = msh_export(*env, args->arg);
	else if (!(ft_strncmp(args->arg[0], "unset", 5 + 1)) && !flag)
		msh_unset(*env, args->arg);
	else if (!(ft_strncmp(args->arg[0], "env", 3 + 1)) && !flag)
		msh_env(*env);
	else if (!(ft_strncmp(args->arg[0], "exit", 4 + 1)) && !flag)
		ft_exit(*env, args);
	else
		ft_fork(args, *env);
	if(last1 != NULL)
	{
		dup2(save_redir1, 1);
	}
	if(last0 != NULL)
	{
		dup2(save_redir0, 0);
	}
}