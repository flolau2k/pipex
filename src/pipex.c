/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/06/02 14:13:59 by flauer           ###   ########.fr       */
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

void	ft_errmsg(char *msg)
{
	char	*message;

	message = ft_strjoin("pipex: ", msg);
	perror(message);
	free(message);
	exit(1);
}

void	ft_err(char *msg)
{
	char	*message;

	message = ft_strjoin("pipex: ", msg);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	free(message);
	exit(1);
}

char	*get_cmd_path(t_pipex *st, char *name, char *env[])
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
	if (!cmd)
		ft_err(name);
	return (cmd);
}

char	*get_cmd(t_pipex *st, char *name, char *env[])
{
	char	*cmd;

	cmd = NULL;
	if (!name)
		return (NULL);
	if (name[0] == '/' || ft_strnstr(name, "./", 2) == name)
		return (ft_strdup(name));
	else
		return (get_cmd_path(st, name, env));
}

void	init(t_pipex *st, char  *argv[], char *env[])
{
	if (access(argv[1], R_OK))
		ft_errmsg(argv[1]);
	if (!access(argv[4], F_OK) && access(argv[4], W_OK))
		ft_errmsg(argv[4]);
	st->fd1 = open(argv[1], O_RDONLY);
	st->fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipe(st->pipe))
		ft_errmsg("pipex: pipe");
	st->argv1 = ft_split(argv[2], ' ');
	st->argv2 = ft_split(argv[3], ' ');
	st->cmd1 = get_cmd(st, st->argv1[0], env);
	st->cmd2 = get_cmd(st, st->argv2[0], env);
	st->env = env;
}

void	child(t_pipex *st)
{
	char *msg;

	dup2(st->pipe[1], STDOUT_FILENO); // redirect STDOUT to pipe input. close STDOUT, and dup st->pipe[1] to STDOUT
	dup2(st->fd1, STDIN_FILENO); // redirect stdin to infile
	close(st->pipe[0]);
	close(st->pipe[1]);
	close(st->fd1);
	close(st->fd2);
	if (!st->cmd1)
		ft_err("no command specified!");
	execve(st->cmd1, st->argv1, st->env);
	msg = ft_strjoin("pipex: parent: ", st->cmd1);
	perror(msg);
	free(msg);
}

void	parent(t_pipex *st)
{
	char *msg;

	dup2(st->pipe[0], STDIN_FILENO); // redirect STDIN to pipe output
	dup2(st->fd2, STDOUT_FILENO);
	close(st->pipe[0]);
	close(st->pipe[1]);
	close(st->fd1);
	close(st->fd2);
	if (!st->cmd2)
		ft_err("no command specified!");
	execve(st->cmd2, st->argv2, st->env);
	msg = ft_strjoin("pipex: child: ", st->cmd2);
	perror(msg);
	free(msg);
}

void	px_init_null(t_pipex *st)
{
	st->argv1 = NULL;
	st->argv2 = NULL;
	st->cmd1 = NULL;
	st->cmd2 = NULL;
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	st;

	px_init_null(&st);
	if (argc != 5)
		return (write(STDERR_FILENO, "Input Error: expected infile \"cmd1\" \"cmd2\" outfile\n", 51));
	init(&st, argv, env);
	if ((st.pid = fork()) == -1)
		perror("pipex: fork");
	if (st.pid)
	{
		wait(&st.stat);
		if (WIFEXITED(st.stat) && WEXITSTATUS(st.stat) == 0)
			parent(&st);
	}
	else
		child(&st);
	cleanup(&st);
	return (WEXITSTATUS(st.stat));
}
