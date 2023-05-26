/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/05/26 14:04:41 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_splits(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
	arr = NULL;
}

void	cleanup(t_pipex *st)
{
	if (st->argv1)
		free_splits(st->argv1);
	if (st->argv2)
		free_splits(st->argv2);
	if (st->cmd1)
		free(st->cmd1);
	if (st->cmd2)
		free(st->cmd2);
	
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

char	*get_cmd(char *name, char *env[])
{
	char	**paths;
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (!name)
		return (NULL);
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

bool	init(t_pipex *st, char  *argv[], char *env[])
{
	if (access(argv[1], R_OK))
		return (false);
	if (!access(argv[4], F_OK) && access(argv[4], W_OK))
		return (false);
	st->fd1 = open(argv[1], O_RDONLY);
	st->fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	pipe(st->pipe);
	st->argv1 = ft_split(argv[2], ' '); // what happens on empty string?
	st->argv2 = ft_split(argv[3], ' ');
	st->cmd1 = get_cmd(st->argv1[0], env);
	st->cmd2 = get_cmd(st->argv2[0], env);
	if (!st->cmd1 || !st->cmd2)
		return (errno = ENOENT,false);
	st->env = env;
	return (true);
}

void	parent(t_pipex *st)
{
	close(st->pipe[0]);
	dup2(st->pipe[1], STDOUT_FILENO); // redirect STDOUT to pipe input
	dup2(st->fd1, STDIN_FILENO); // redirect stdin to infile
	execve(st->cmd1, st->argv1, st->env);
	perror(strerror(errno));
}

void	child(t_pipex *st)
{
	close(st->pipe[1]);
	dup2(st->pipe[0], STDIN_FILENO); // redirect STDIN to pipe output
	dup2(st->fd2, STDOUT_FILENO);
	execve(st->cmd2, st->argv2, st->env);
	perror(strerror(errno));
}

int	main(int argc, char *argv[], char *env[])
{
	// create a data structure: 
	t_pipex	st;

	// input to be expected:
	// 4 arguments: infile cmd1 cmd2 outfile
	if (argc != 5)
		return (write(STDERR_FILENO, "Input Error\n", 12));
	if (!init(&st, argv, env))
		return (cleanup(&st), perror(strerror(errno)), errno);
	st.pid = fork();
	if (st.pid)
		parent(&st);
	else
		child(&st);
	cleanup(&st);
	return (0);
}
