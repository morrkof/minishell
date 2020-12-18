/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:19:32 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/18 15:07:41 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(t_env **env, t_args *args)
{
	int status;
	char *res;

	if (args->arg[1] != NULL)
		status = ft_atoi(args->arg[1]);
	else
		status = 0;
	res = ft_itoa(status);
	set_env(env, "?", res);
	free(res);
	exit (status);
}

void	ft_echo(char **args, t_env **env)
{
	int i;
	int flag;

	flag = 0;
	i = 1;
	while (args[i] != NULL && !(ft_strncmp(args[i], "-n", 3)))
	{
		flag = 1;
		i++;
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
	set_env(env, "?", "0");
}

void    ft_cd(char **args, t_env **env)
{
	int		status;
	char	*res;

    if (status = chdir(args[1]))
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	res = ft_itoa(status * -1);
	set_env(env, "PWD", getcwd(NULL, 0));
	set_env(env, "?", res);
	free(res);
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
		}
		closedir(dir);
		i++;
	}
	
	return(NULL);
}

int    ft_fork(t_args *arg, t_env **env)
{
    pid_t pid;
    pid_t wpid;
    int status;
	static int saved;
	int pipefd[2];
	int savefd1;
	int savefd0;
	char *abs_path;
	char *tmp;
	char *exec_path;

	if (arg->flag_in_pipe)
	{
		savefd0 = dup(0);
		dup2(saved, 0);
		close(saved);
	}
	if (arg->flag_out_pipe)
	{
		pipe(pipefd);
		savefd1 = dup(1);
		saved = pipefd[0];
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	(void)wpid;
	exec_path = arg->arg[0];
	if (!(ft_strchr(arg->arg[0], '/')))
	{
		abs_path = get_path(arg->arg[0], (get_env(env, "PATH"))->val);
		if (abs_path == NULL)
		{
			write(2, arg->arg[0], ft_strlen(arg->arg[0]));
			write(2, ": command not found\n", ft_strlen(": command not found\n"));
			set_env(env, "?", "127");
			return (1);
		}
		tmp = ft_strjoin(abs_path, "/");
		exec_path = ft_strjoin(tmp, arg->arg[0]);
	}
	pid = fork();
    if (pid == 0) // это дочка
	{
		if (execve(exec_path, arg->arg, struct_to_char(env)) == -1)
		{
			perror ("error");
			exit (-1);
		}
	}
	else if (pid < 0) // это ошибка
			perror ("errorg");
	else // это родитель
	{
		while (wpid = waitpid(pid, &status, WUNTRACED))
		{
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break ;
		}
		set_env(env, "?", ft_itoa(WEXITSTATUS(status)));
	}
	if (arg->flag_in_pipe)
	{
		dup2(savefd0, 0);
		close(savefd0);
	}
	if (arg->flag_out_pipe)
	{
		dup2(savefd1, 1);
		close(savefd1);
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
	if (!(ft_strncmp(args->arg[0], "echo", 5)) && !flag)
		ft_echo(args->arg, *env);
	else if (!(ft_strncmp(args->arg[0], "pwd", 4)) && !flag)
		ft_pwd(*env);
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