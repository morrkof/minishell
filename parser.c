/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:13:11 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/24 16:07:10 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (NULL);
	if (!(substr = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (j++ < len && s[start] != '\0')
	{
		c = s[start];
		if (c == '\\')
			substr[i++] = s[++start];
		else if (c != '\'' && c != '\"')
			substr[i++] = c;
		start++;
	}
	substr[i] = '\0';
	if (substr[0] != '\0')
		return (substr);
	free(substr);
	return (NULL);
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
	return (red);
}
