/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:03:30 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/19 01:54:29 by ppipes           ###   ########.fr       */
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

typedef	struct		s_red
{
	int				red;			// > - 1;  >> - 2; < - 3; << - 4;
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
/*
typedef struct		s_args
{
	char			**args;
	int				in_pipe;
	int				out_pipe;
	struct s_args	*next;
	int				next_type;
}					t_args;
*/

void	parse_line(t_args *args, char *line);
void	execute_command(t_args *args);

#endif
