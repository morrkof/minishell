/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:12:21 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/07 19:44:35 by miphigen         ###   ########.fr       */
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

void	hello()
{
	char	*pwd;
	
	write(1, "msh:", 4); // приглашение ввода
	pwd = getcwd(NULL, 0);
	write (1, pwd, ft_strlen(pwd));
	write(1, "$ ", 2);
	free(pwd);
}

void	hello_sigquit()
{
	write(1,"\b\b  \b\b", 6);
	SIG_IGN;
}

void	hello_sigint()
{
	write(1, "\n", 1);
	SIG_IGN;
	hello();
}

int main(int ac, char **av, char **env, int res)
{
	char	*line;
	t_args	args; // это отправим в парсер
	t_args	*cur;
	t_env	**env_var2 = NULL;
	char	*pwd;

	(void)ac;
	(void)av;	
	env_var2 = char_to_struct(env);
	res = 1;
	while (1)
	{
		signal(SIGINT, hello_sigint);
		signal(SIGQUIT, hello_sigquit);
		res == 0 ? 0 : hello();//приглашение ввода
		res = get_next_line(0, &line); // считываем строку из stdin
		if (res == 0)
			continue;
		parse_line(&args, line); // тут будет парсер
		cur = &args;
		while (cur != NULL)
		{
			process_variables(cur, struct_to_char(env_var2));
			execute_command(cur, &env_var2);	// сюда структура должна попасть уже заполненной
			cur = cur->next;
		}
		free(line);
	}
	return (0);
}