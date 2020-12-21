

#include "minishell.h"

void	msh_env(t_env **env)
{
	int		i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (env[i]->name == NULL)
		{	
			continue;
		}
		write(1, env[i]->name, ft_strlen(env[i]->name));
		write(1, "=", 1);
		write(1, env[i]->val, ft_strlen(env[i]->val));
		write(1, "\n", 1);
	}
	g_status = 0;
}

void	msh_unset(t_env **env, char **arr)
{
	int		i;
	int		res;
	char	*s;

	s = arr[1];
	if (arr[1] == NULL)
		return ;
	i = -1;
	while (env[++i] != NULL)
	{
		if (env[i]->name == NULL)
			continue;
		if (!(res = ft_strcmp(s, env[i]->name)))
		{
			free(env[i]->name);
			env[i]->name = NULL;
			free(env[i]->val);
			env[i]->val = NULL;
			break;
		}
	}
	g_status = 0;
}
