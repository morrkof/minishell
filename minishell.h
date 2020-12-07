/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:17:15 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/07 12:37:55 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
# include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>

typedef	struct		s_env
{
	char			*name;
	char			*val;
}					t_env;

typedef	struct		s_red
{
	int				red;			// > - 1;  >> - 2; < - 3; << - 4; 2> - 5
	char			*file;			// название файла
	struct s_red	*next;			//
	struct s_red	*prev;			//
}					t_red;

typedef struct 		s_args
{
	char			**arg;			// массив строк с аргументами и именем
	int				n_flag;			// флаг у эха
	t_red			*red;			// список редиректов (их может быть много)
	int				flag_out_pipe;	// если пайп справа, то = 1
	int				flag_in_pipe;	// если пайп слева, то = 1
	struct s_args	*next;			// указатель на следующий элемент
	struct s_args	*prev;			// указатель на предыдущий элемент
}					t_args;

typedef enum		e_sEscape
{
	ESCAPED,
	NONESCAPED
}					t_s_escape;

typedef enum		sParser
{
	DOUBLE_Q,
	SINGLE_Q,
	NON_Q
}					t_s_parser;

t_args	*parse_line(t_args *args, char *line);
void	print_2d_char(char **array, char c);
void	execute_command(t_args *args, t_env ***env);
t_env	*get_env(t_env **env, char *name);
int		set_env(t_env **env, char *name, char *val);
char	**struct_to_char(t_env **src);
t_env **char_to_struct(char **src);
char	*get_path(char *command, char *path);
void	process_variables(t_args *args, char **env_var2);
void	msh_env(t_env **env);
void	msh_unset(t_env **env, char **arr);
t_env	**msh_export(t_env **env, char **arr);


#endif
