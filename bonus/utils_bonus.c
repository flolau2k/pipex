/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:28:00 by flauer            #+#    #+#             */
/*   Updated: 2023/06/18 15:51:09 by flauer           ###   ########.fr       */
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

void	ft_errp(char *msg)
{
	char	*message;

	if (msg)
	{
		message = ft_strjoin("pipex: ", msg);
		perror(message);
		free(message);
	}
	else
		perror("pipex: ");
	exit(127);
}

void	ft_err(char *msg)
{
	char	*message;

	message = ft_strjoin("pipex: ", msg);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	free(message);
	free(msg);
	exit(127);
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
