/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:28:00 by flauer            #+#    #+#             */
/*   Updated: 2023/06/23 18:06:21 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_splits(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}

char	**get_env(char *env[], char *key)
{
	int		i;
	char	*trim;
	char	**ret;

	i = 0;
	trim = NULL;
	ret = NULL;
	if (ft_strlen(key) == 0)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], key, ft_strlen(key)))
		{
			trim = ft_strtrim(env[i], key);
			ret = ft_split(trim, ':');
			return (free(trim), ret);
		}
		++i;
	}
	return (NULL);
}

char	*get_cmd_path(char *name, char *env[])
{
	char	**paths;
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	paths = get_env(env, "PATH=");
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(path, name);
		free(path);
		if (!access(cmd, X_OK))
			break ;
		free(cmd);
		cmd = NULL;
		++i;
	}
	free_splits(paths);
	return (cmd);
}

char	*get_cmd(char *name, char *env[])
{
	char	*ret;

	ret = NULL;
	if (!name)
		return (NULL);
	if (name[0] == '/' || ft_strnstr(name, "./", 2) == name)
		return (ft_strdup(name));
	ret = get_cmd_path(name, env);
	if (!ret && ft_strnstr(name, "/", ft_strlen(name)))
		return (ft_strdup(name));
	return (ret);
}
