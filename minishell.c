/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <student.21-school.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:17:56 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/26 15:36:31 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(char **dest, char **src)
{
	size_t	length;
	int		i;

	length = 0;
	while (src[length])
		++length;
	dest = malloc(sizeof(char *) * (length + 10));
	i = -1;
	while (src[++i])
	{
		dest[i] = src[i];
	}
	dest[i] = NULL;
	return (dest);
}

int main(int ac, char **av, char **env)
{
	char	*line;
	t_args	args; // это отправим в парсер
	char	**env_var = NULL;
	char	*pwd;
	
	(void)ac;
	(void)av;	
	env_var = copy_array(env_var, env);
	
	//print_2d_char(env, '\n');
	while (1)
	{
		write(1, "bash: ", 5); // приглашение ввода
		pwd = getcwd(NULL, 0);
		write (1, pwd, ft_strlen(pwd));
		write(1, "$ ", 2);
		free(pwd);
		get_next_line(0, &line); // считываем строку из stdin
		parse_line(&args, line, env_var); // тут будет парсер
		execute_command(&args, env_var);	// сюда структура должна попасть уже заполненной
		//printf("READ THIS: %s\n", line); // распечатаем что мы считали
		free(line);
	}
	return (0);
}