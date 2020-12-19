/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <student.21-school.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:22:41 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/19 19:32:54 by ppipes           ###   ########.fr       */
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

typedef	struct		s_env
{
	char			*name;
	char			*val;
}					t_env;

typedef	struct		s_red
{
	int				red;// > - 1;  >> - 2; < - 3; << - 4; 2> - 5
	char			*file;
	struct s_red	*next;
	struct s_red	*prev;
}					t_red;

typedef struct		s_args
{
	char			**arg;
	int				n_flag;
	t_red			*red;
	int				flag_out_pipe;// если пайп справа, то = 1
	int				flag_in_pipe;// если пайп слева, то = 1
	struct s_args	*next;
	struct s_args	*prev;
	int				sq_flag;
}					t_args;

typedef enum		e_sEscape
{
	ESCAPED,
	NONESCAPED
}					t_s_escape;

typedef enum		e_sParser
{
	DOUBLE_Q,
	SINGLE_Q,
	NON_Q
}					t_s_parser;

t_args				*parse_line(t_args *args, char *line);
void				print_2d_char(char **array, char c);
void				execute_command(t_args *args, t_env ***env);
t_env				*get_env(t_env **env, char *name);
void				set_env(t_env ***env, char *name, char *val);
char				**struct_to_char(t_env **src);
t_env				**char_to_struct(char **src);
char				*get_path(char *command, char *path);
void				process_variables(t_args *args, char **env_var2);
void				msh_env(t_env **env);
void				msh_unset(t_env **env, char **arr);
t_env				**msh_export(t_env **env, char **arr);
t_env				**copy_env(t_env **dst, t_env **src);
t_env				*split_arg(char *s);
t_env				**msh_export(t_env **env, char **arr);
t_env				**set_new_env(t_env **src, char *name, char *val);
void				free_t_env(t_env *env);
void				free_2d_array(char **arr);
void				free_2d_env (t_env **env);
void				free_red(t_red *red);
void				free_args(t_args *args);
int		ft_exit(t_env **env, t_args *args);

#endif
