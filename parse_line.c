/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:08:52 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/23 16:21:44 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*parse_line(t_args *args, char *s)
{
	t_s_escape	state_e;
	t_s_parser	state_p;
	int			i;
	int			start;
	char		**arg;
	char		c;
	t_args		*head;
	int			red;

	head = args;
	args_init(args);
	if (ft_strchr(s, '\''))
		args->sq_flag = 1;
	arg = args->arg;
	state_p = NON_Q;
	state_e = NONESCAPED;
	i = -1;
	red = 0;
	start = 0;
	while (++i >= 0)
	{
		c = s[i];
		if (state_e == NONESCAPED && c == '\\')
		{
			state_e = ESCAPED;
			continue;
		}
		else if (state_e == ESCAPED)
		{
			state_e = NONESCAPED;
			continue;
		}
		if (state_p == DOUBLE_Q && c == '\"')
			state_p = NON_Q;
		else if (state_p == SINGLE_Q && c == '\'')
			state_p = NON_Q;
		else if (state_p == NON_Q)
		{
			if (c == '"')
				state_p = DOUBLE_Q;
			else if (c == '\'')
				state_p = SINGLE_Q;
			else if ((c == '|' || c == ';'))
			{
				red == 0 ? arg = add_arg(s, &i, &start, arg) :
					add_red(s, &i, &start, &red, args);
				args = add_command(args, c, &arg);
			}
			else if ((ft_isspace(c) || c == '\n' || c == '\0'))
				red == 0 ? arg = add_arg(s, &i, &start, arg) :
					add_red(s, &i, &start, &red, args);
			else if ((c == '<' || c == '>'))
			{
				red == 0 ? arg = add_arg(s, &i, &start, arg) :
					add_red(s, &i, &start, &red, args);
				if (c == '<' && s[i + 1] == '<')
				{
					red = 4;
					i++;
					start++;
				}
				else if (c == '>' && s[i + 1] == '>')
				{
					red = 2;
					i++;
					start++;
				}
				else if (c == '<')
					red = 3;
				else if (c == '>')
					red = 1;
			}
		}
		if (c == '\0')
			break ;
	}
//	printf("line = >%s<\n", s);
//	print_args(head);
	return (head);
}
