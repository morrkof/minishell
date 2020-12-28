/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:08:52 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/25 21:35:14 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_2d_char(char **array, char c)//
{
	puts("print_2d_char():");

	while (*array != NULL)
	{
		printf(">%s<%c ", *array, c);
		array++;
	}
	printf("\n");
}

void	print_args(t_args *args)//
{
	t_red	*red;
	
	while (args != NULL)
	{
		printf("\n%p\nflag_in_out = %d/%d\n", args, args->flag_in_pipe, args->flag_out_pipe);
		print_2d_char(args->arg, ',');
		red = args->red;
		while (red != NULL)
		{
			printf("redirect: file = %s, type = %d\n", red->file, red->red);
			red = red->next;
		}
		args = args->next;
		puts("");
	}
}
t_args	*parse_line(t_args *args, char *s)
{
	t_local_vars	l;
	t_args			*head;

	head = args;
	args_init(args);
	if (args->arg == NULL)
		return (head);
	if (ft_strchr(s, '\''))
		args->sq_flag = 1;
	l.arg = args->arg;
	l.state_p = NON_Q;
	l.state_e = NONESCAPED;
	l.i = -1;
	l.red = 0;
	l.start = 0;
	while_loop(args, s, &l);
	//print_args(head);//
	return (head);
}

void	while_loop(t_args *args, char *s, t_local_vars *l)
{
	while (++l->i >= 0)
	{
		l->c = s[l->i];
		if (l->state_e == NONESCAPED && l->c == '\\')
		{
			l->state_e = ESCAPED;
			continue;
		}
		else if (l->state_e == ESCAPED)
		{
			l->state_e = NONESCAPED;
			continue;
		}
		if (l->state_p == DOUBLE_Q && l->c == '\"')
			l->state_p = NON_Q;
		else if (l->state_p == SINGLE_Q && l->c == '\'')
			l->state_p = NON_Q;
		else if (l->state_p == NON_Q)
		{
			if_non_q_state(&args, s, l);
		}
		if (l->c == '\0')
			break ;
	}
}

void	if_non_q_state(t_args **args_ptr, char *s, t_local_vars *l)
{
	t_args	*args;

	args = *args_ptr;
	if (l->c == '"')
		l->state_p = DOUBLE_Q;
	else if (l->c == '\'')
		l->state_p = SINGLE_Q;
	else if ((l->c == '|' || l->c == ';'))
	{
		l->red == 0 ? l->arg = add_arg(s, &l->i, &l->start, l->arg) :
			add_red(s, l, args, NULL);
		*args_ptr = add_command(args, l->c, &l->arg);
	}
	else if ((ft_isspace(l->c) || l->c == '\n' || l->c == '\0'))
		l->red == 0 ? l->arg = add_arg(s, &l->i, &l->start, l->arg) :
			add_red(s, l, args, NULL);
	else if ((l->c == '<' || l->c == '>'))
	{
		if_red(args, s, l);
	}
}

void	if_red(t_args *args, char *s, t_local_vars *l)
{
	l->red == 0 ? l->arg = add_arg(s, &l->i, &l->start, l->arg) :
		add_red(s, l, args, NULL);
	if (l->c == '<' && s[l->i + 1] == '<')
	{
		l->red = 4;
		l->i++;
		l->start++;
	}
	else if (l->c == '>' && s[l->i + 1] == '>')
	{
		l->red = 2;
		l->i++;
		l->start++;
	}
	else if (l->c == '<')
		l->red = 3;
	else if (l->c == '>')
		l->red = 1;
}

void	add_red(char *s, t_local_vars *l, t_args *args, char *str)
{
	t_red	*ptr;

	if (!(str = msh_substr(s, l->start, l->i - l->start)))
	{
		l->start++;
		return ;
	}
	l->start = l->i + 1;
	if (args->red == NULL)
	{
		args->red = red_init(args->red);
		ptr = args->red;
	}
	else
	{
		ptr = args->red;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = red_init(ptr->next);
		ptr = ptr->next;
	}
	ptr->red = l->red;
	ptr->file = ft_strtrim(str, " \t\r\n\f\v");
	free(str);
	l->red = 0;
}
