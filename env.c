/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:42:50 by miphigen          #+#    #+#             */
/*   Updated: 2020/11/25 22:31:35 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **env)
{
	while (*env)
	{
		write(1, *env, ft_strlen(*env));
		env++;
	}
}

void	export(char **env, char *s)
{
	
}

void	unset(char **env, char *s)
{
	
}
