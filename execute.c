/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:54:56 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/07 17:59:32 by ppipes           ###   ########.fr       */
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

void    ft_cd(char **args, t_env **env)
{
    chdir(args[1]);
	set_env(env, "PWD", getcwd(NULL, 0));
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



void	ft_pwd()
{
	char *buf;

	buf = getcwd(NULL, 0);
	write (1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
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

void    ft_fork(char **args, t_env **env)
{
    pid_t pid;
    pid_t wpid;
    int status;
	char *abs_path;
	char *tmp;
	char *exec_path;

    (void)wpid;
	exec_path = args[0];
	if(!(ft_strchr(args[0], '/')))
	{
		abs_path = get_path(args[0], (get_env(env, "PATH"))->val);
		tmp = ft_strjoin(abs_path, "/");
		exec_path = ft_strjoin(tmp, args[0]);
	}
	pid = fork();
	// printf("command - %s \nargument %s\n", exec_path, args[0]);
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
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

int	set_redirect(t_args *args)
{
	t_red	*cur;
	int fd;

	cur = &args->red;
	while(cur + 1 != NULL)
	{
		fd = open(cur->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		close(fd);
		cur = cur->next;
	}
	if (cur->red == 1)
		fd = open(cur->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (cur->red == 2)
		fd = open(cur->file, O_CREAT | O_APPEND | O_RDWR, 0644);
	else if (cur->red == 3)
		fd = open(cur->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (cur->red == 4)
		fd = open(cur->file, O_CREAT | O_APPEND | O_RDWR, 0644);
	return (fd);
}


void	execute_command(t_args *args, t_env **env)
{
	char *line;
	int	fd_redir;
	line = args->arg[0];
	if (args->red != NULL)
	{
		fd_redir = set_redirect(args);
	}

	if (!(ft_strncmp(line, "echo", 4)))
		ft_echo(args->arg);
	else if (!(ft_strncmp(line, "pwd", 3)))
		ft_pwd();
	else if (!(ft_strncmp(line, "cd", 2)))
		ft_cd(args->arg, env);
	else if (!(ft_strncmp(line, "export", 6)))
		printf("check export\n");
	else if (!(ft_strncmp(line, "unset", 5)))
		printf("check unset\n");
	else if (!(ft_strncmp(line, "env", 3)))
		printf("check env\n");
	else if (!(ft_strncmp(line, "exit", 4)))
		exit(0);
	else
		ft_fork(args->arg, env);
}