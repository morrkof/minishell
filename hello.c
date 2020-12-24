/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:25:46 by miphigen          #+#    #+#             */
/*   Updated: 2020/12/24 16:25:59 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hello(void)
{
	char	*pwd;

	write(1, "msh:", 4);
	pwd = getcwd(NULL, 0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "$ ", 2);
	free(pwd);
}

void	hello_sigquit(int i)
{
	i = i;
	write(1, "\b\b  \b\b", 6);
	SIG_IGN;
}

void	hello_sigint(int i)
{
	i = i;
	write(1, "\n", 1);
	SIG_IGN;
	g_res = 0;
	free(g_line);
	g_line = ft_strdup("");
	hello();
}
