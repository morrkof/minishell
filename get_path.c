/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:15:17 by ppipes            #+#    #+#             */
/*   Updated: 2020/12/23 17:39:24 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_current_path(char *path)
{
	char	*pwd;
	char	*tmp;
	char	*result;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin(pwd, ":");
	free(pwd);
	result = ft_strjoin(tmp, path);
	free(tmp);
	return (result);
}

char	**split_paths(char *path)
{
	char	**paths;

	path = add_current_path(path);
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}

char	*get_path(char *command, char **paths)
{
	char			*result;
	DIR				*dir;
	struct dirent	*ent;
	int				i;

	i = 0;
	while (paths[i])
	{
		dir = opendir(paths[i]);
		while ((ent = readdir(dir)) != 0)
		{
			if (!(ft_strcmp(command, ent->d_name)))
			{
				closedir(dir);
				result = ft_strdup(paths[i]);
				free_2d_array(paths);
				return (result);
			}
		}
		i++;
		closedir(dir);
	}
	free_2d_array(paths);
	return (NULL);
}
