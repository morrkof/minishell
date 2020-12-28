/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:13:11 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/25 18:13:14 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{	
			substr[++i] = s[++start];
			--len;
		}
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
	if (args->next == NULL)
		return (args);
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
	if (red == NULL)
		return (NULL);
	red->red = 0;
	red->file = NULL;
	red->next = NULL;
	return (red);
}
