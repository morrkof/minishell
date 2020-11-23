/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:02:28 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/23 18:30:43 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	char *pwd;
	// t_args args; // это отправим в парсер

	while (1)
	{
		write(1, "MINISHELL@42:", 13); // приглашение ввода
		pwd = getcwd(NULL, 0);
		write (1, pwd, ft_strlen(pwd));
		write(1, "$ ", 2);
		free(pwd);
		get_next_line(0, &line); // считываем строку из stdin
		// parse_line(&args, line); // тут будет парсер
		execute_command(line);	// сюда структура должна попасть уже заполненной
		// printf("READ THIS: %s\n", line); // распечатаем что мы считали
		free(line);
	}
	return (0);
}