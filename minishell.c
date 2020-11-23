/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:02:28 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/22 15:39:46 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char *line;
	 t_args args; // это отправим в парсер

	ac = ac;
	av = av;	
	print_2d_char(env, '\n');
	while (1)
	{
		write(1, "bash: ", 5); // приглашение ввода
		get_next_line(0, &line); // считываем строку из stdin
		parse_line(&args, line, env); // тут будет парсер
		// execute_command(&args);	// сюда структура должна попасть уже заполненной
		//printf("READ THIS: %s\n", line); // распечатаем что мы считали
		free(line);
	}
	return (0);
}