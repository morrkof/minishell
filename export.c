

#include "minishell.h"

t_env	**copy_env(t_env **dst, t_env **src)
{
	int	i;

	i = -1;
	while (src[++i] != NULL)
	{
		dst[i] = src[i];
	}
	dst[i + 1] = NULL;
	return (dst);
}

t_env	*split_arg(char *s)
{
	t_env	*env;
	int		start;

	start = ft_strchr(s, '=') - s;
	env = malloc(sizeof(t_env));
	env->name = ft_substr(s, 0, start);
	start++;
	env->val = ft_substr(s, start, ft_strlen(s) - start);
	return env;
}

void	free_t_env(t_env *env)
{
	free(env->name);
	free(env->val);
	free(env);
}

t_env	**copy_env_ptrs(t_env **dest, t_env **src)
{
	int	i;

	i = -1;
	while (src[++i] != NULL)
	{
		dest[i] = src[i];
	}
	dest[i] = NULL;
	return (dest);
}

int	more(t_env *lhs, t_env *rhs)
{
	if (ft_strcmp(lhs->name, rhs->name) > 0)
		return (1);
	else
		return (0);
}

void	swap(t_env **a, t_env **b)
{
	t_env	*c;
	
	c = *a;
	*a = *b;
	*b = c;
}

void	sort(t_env	**env)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	while (env[size] != NULL)
		size++;
	i = size;
	while (i > 0)
	{
		j = 0;
		while (j < i - 1)
		{
			if (more(env[j], env[j + 1]))
				swap(&env[j],&env[j + 1]);
			j++;
		}
		i--;
	}
}

void	env_alph_order(t_env **env)
{
	t_env	**copy;
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;	
	copy = malloc(sizeof(t_env *) * (i + 1));
	copy = copy_env_ptrs(copy, env);
	sort(copy);
	i = -1;
	while (copy[++i] != NULL)
	{
		if (copy[i]->name == NULL)
		{	
			continue;
		}
		write(1, "declare -x ", 11);
		write(1, copy[i]->name, ft_strlen(copy[i]->name));
		write(1, "=", 1);
		write(1, copy[i]->val, ft_strlen(copy[i]->val));
		write(1, "\n", 1);
	}
	free(copy);
	

}

t_env	**msh_export(t_env **env, char **arr)
{
	int		i;
	t_env	**copy;
	t_env	*temp;

	if (arr[1] == NULL)
	{
		env_alph_order(env);
		return (env);
	}
	temp = split_arg(arr[1]);
	i = -1;
	while (env[++i] != NULL)
	{	
		if (ft_strcmp(env[i]->name, temp->name) == 0)
		{	
			env[i]->val = ft_strdup(temp->val);
			return (env);
		}
	}
	copy = malloc(sizeof(t_env *) * (i + 2));
	copy = copy_env(copy, env);

	copy[i] = temp;
	free(env);
	// set_env(&copy, "?", "0");
	g_status = 0;
	return (copy);
}
