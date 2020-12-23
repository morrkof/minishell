/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:06:40 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/23 16:06:43 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirect(char *s, t_args *args);

void	print_args(t_args *args)
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

void	print_2d_char(char **array, char c)
{
	puts("print_2d_char():");
	
	while (*array != NULL)
	{
		printf(">%s<%c", *array, c);
		array++;
	}
	printf("\n");
}

void	args_init(t_args *args)
{
	args->n_flag = 0;
	args->flag_out_pipe = 0;
	args->flag_in_pipe = 0;
	args->next = NULL;
	args->red = NULL;
	args->arg = malloc(sizeof(char *) * 100);
	args->arg[0] = NULL;
	args->sq_flag = 0;
}

char	*msh_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	char	c;
	size_t	j;

	if (len == 0)
		return NULL;
	if (!(substr = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (j++ < len && s[start] != '\0')
	{
			c = s[start];
		if (c == '\\')
		{
			substr[i++] = s[++start];
		}
		else if (c != '\'' && c != '\"')
		{	
			substr[i++] = c;
		}
		start++;
	}
	substr[i] = '\0';
	if (substr[0] != '\0')
		return (substr);
	free(substr);
	return NULL;
}

char	**add_arg(char *s, int *i, int *start, char **arr)
{
	*arr = msh_substr(s, *start, *i - *start);
	if (*arr != NULL)
	{
		arr++;
		*arr = NULL;
	}
	while (s[*i] != '\0' && ft_isspace(s[*i + 1]))
		(*i)++;
	*start = *i + 1;
	return (arr);
}

t_args	*add_command(t_args *args, char c, char ***arg)
{
	if (c == '|')
	args->flag_out_pipe = 1;
	args->next = malloc(sizeof(t_args));
	args->next->prev = args;
	args_init(args->next);
	args = args->next;
	*arg = args->arg;
	if (c == '|')
		args->flag_in_pipe = 1;
	return (args);
}

t_red	*red_init(t_red *red)
{
	red = malloc(sizeof(t_red));
	red->red = 0;
	red->file = NULL;
	red->next = NULL;
	red->prev = NULL;
	return (red);
}

void	add_red(char *s, int *i, int *start, int *red, t_args *args)
{
	char	*str;
	t_red	*ptr;

	if (!(str = msh_substr(s, *start, *i - *start)))
	{	
		(*start)++;
		return ;
	}
	*start = *i + 1;
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
	ptr->red = *red;
	ptr->file = ft_strtrim(str, " \t\r\n\f\v");
	free(str);
	*red = 0;
}

t_args	*parse_line(t_args *args, char *s)
{
	t_s_escape state_e;
	t_s_parser state_p;
	int			i;//
	int			start;//
	char		**arg;
	char		c;//
	t_args		*head = args;
	int			red;

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
			break;
	}
//	printf("line = >%s<\n", s);
//	print_args(head);
	return (head);
}
