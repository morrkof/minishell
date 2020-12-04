/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:12:21 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/04 22:48:40 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env **char_to_struct(char **src)
{
	t_env	**dest;
	size_t	len;
	size_t	i;
	int		eq;

	len = 0;
	i = 0;
	while(src[len])
		len++;
	dest = malloc(sizeof(t_env *) * (len + 1));
	while(i < len)
	{
		dest[i] = malloc(sizeof(t_env));
		eq = ft_strchr(src[i], '=') - src[i];
		dest[i]->name = ft_substr(src[i], 0, eq);
		dest[i]->val = ft_substr(src[i], eq + 1, ft_strlen(src[i]) - eq);
		// printf("SRC %s \n NAME %s \n VALUE %s \n", src[i], dest[i]->name, dest[i]->val);
		i++;
	}
	dest[i] = NULL;
	return(dest);
}

char	**struct_to_char(t_env **src)
{
	char **dest;
	char	*tmp;
	size_t	len;
	size_t i;

	len = 0;
	i = 0;
	while(src[len])
		len++;
	dest = malloc(sizeof(char *) * (len + 1));
	while(i < len)
	{
		tmp = ft_strjoin(src[i]->name, "=");
		dest[i] = ft_strjoin(tmp, src[i]->val);
		free(tmp);
		i++;
	}
	dest[i] = NULL;
	return(dest);

}

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
	t_args	*cur;
	// char	**env_var = NULL;
	t_env	**env_var2 = NULL;
	char	*pwd;
	
	(void)ac;
	(void)av;	
	// env_var = copy_array(env_var, env);
	env_var2 = char_to_struct(env);
	//print_2d_char(env, '\n');
	// printf("%s\n", (get_env(env_var2, "PATH"))->val);
	// set_env(env_var2, "PATH", "blabla");
	// printf("%s\n", (get_env(env_var2, "PATH"))->val);
	// get_path("ls", "/home/anastasia/Desktop/minishell");
	while (1)
	{
		write(1, "msh:", 4); // приглашение ввода
		pwd = getcwd(NULL, 0);
		write (1, pwd, ft_strlen(pwd));
		write(1, "$ ", 2);
		free(pwd);
		get_next_line(0, &line); // считываем строку из stdin
		parse_line(&args, line, struct_to_char(env_var2)); // тут будет парсер
		cur = &args;
		while (cur != NULL)
		{
			process_variables(cur, struct_to_char(env_var2));
			execute_command(cur, env_var2);	// сюда структура должна попасть уже заполненной
			cur = cur->next;
		}

		//printf("READ THIS: %s\n", line); // распечатаем что мы считали
		free(line);
	}
	return (0);
}