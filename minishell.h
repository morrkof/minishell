/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:22:41 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/29 10:33:13 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>

int					g_status;
int					g_res;
char				*g_line;

typedef	struct		s_red
{
	int				red;
	char			*file;
	struct s_red	*next;
}					t_red;

typedef struct		s_savefd
{
	t_red			*last0;
	t_red			*last1;
	int				redir0;
	int				redir1;
}					t_savefd;

typedef struct		s_pipe
{
	int				pipefd[2];
	int				savefd0;
	int				savefd1;
}					t_pipe;

typedef	struct		s_env
{
	char			*name;
	char			*val;
}					t_env;

typedef struct		s_args
{
	char			**arg;
	int				n_flag;
	t_red			*red;
	int				flag_out_pipe;
	int				flag_in_pipe;
	struct s_args	*next;
	int				sq_flag;
}					t_args;

typedef enum		e_s_escape
{
	ESCAPED,
	NONESCAPED
}					t_s_escape;

typedef enum		e_s_parser
{
	DOUBLE_Q,
	SINGLE_Q,
	NON_Q
}					t_s_parser;

typedef struct		s_local_vars
{
	t_s_escape		state_e;
	t_s_parser		state_p;
	int				i;
	int				start;
	char			**arg;
	char			c;
	int				red;

}					t_local_vars;

t_args				*parse_line(t_args *args, char *line);
void				print_2d_char(char **array, char c);
void				execute_command(t_args *args, t_env ***env);
void				find_last_redirect(t_args *args, t_red **last0, \
						t_red **last1);
void				set_redirect(t_args *args, t_savefd *save);
void				unset_redirect(t_savefd *save);
t_env				*get_env(t_env **env, char *name);
void				set_env(t_env ***env, char *name, char *val);
char				**str2ch(t_env **src);
t_env				**ch2str(char **src);
char				*get_path(char *command, char **paths);
char				**split_paths(char *path);
char				*add_current_path(char *path);
void				process_variables(t_args *args, t_env **env);
void				msh_env(t_env **env);
void				msh_unset(t_env **env, char **arr);
t_env				**msh_export(t_env **env, char **arr);
t_env				**copy_env(t_env **dst, t_env **src);
t_env				*split_arg(char *s);
t_env				**msh_export(t_env **env, char **arr);
void				free_t_env(t_env *env);
void				free_2d_array(char **arr);
void				free_2d_env (t_env **env);
void				free_red(t_red *red);
void				free_args(t_args *args);
int					ft_exit(t_env **env, t_args *args);
void				env_alph_order(t_env **env);
void				args_init(t_args *args);
char				**add_arg(char *s, int *i, int *start, char **arr);
t_args				*add_command(t_args *args, char c, char ***arg);
void				print_args(t_args *args);
void				while_loop(t_args *args, char *s, t_local_vars *var);
void				if_non_q_state(t_args **args_ptr, char *s, t_local_vars *l);
void				if_red(t_args *args, char *s, t_local_vars *l);
char				*msh_substr(char *s, unsigned int start, size_t len, char *substr);
t_red				*red_init(t_red *red);
void				ft_cd(char **args, t_env **env);
void				ft_pwd(void);
void				ft_echo(char **args);
void				print_errno_error(void);
int					ft_fork(t_args *arg, t_env **env, int flag);
char				*find_exec_path(t_args *arg, t_env **env);
void				set_pipes(t_args *arg, t_pipe *pipes, int flag);
void				unset_pipes(t_args *arg, t_pipe *pipes, int flag);
void				add_red(char *s, t_local_vars *l, t_args *args, char *str);
void				hello(void);
void				hello_sigquit(int i);
void				hello_sigint(int i);
int					arrlen(t_env **src);
int					check_args(t_args *args);
int					check_arr(t_env **env, char **arr);
int					check_exist(t_env **env, t_env *temp);

#endif
