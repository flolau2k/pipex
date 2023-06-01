/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/06/01 13:05:58 by flauer           ###   ########.fr       */
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

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		++i;
	return (i);
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

void	ft_error(t_pipex *st, ...)
{
	va_list	args;
	char	*message;

	va_start(args, st);
	message = va_arg(args, char *);
	if (message)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		message = va_arg(args, char *);
		while (message)
		{
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, message, ft_strlen(message));
			message = va_arg(args, char *);
		}
		write(STDERR_FILENO, "\n", 1);
	}
	va_end(args);
	cleanup(st);
	exit(-1);
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

char	*get_cmd_pwd(t_pipex *st, char *name, char *env[])
{
	char	**pwd;
	char	*cmd;
	char	*tname;

	pwd = get_env(env, "PWD=");
	if (ft_arrlen(pwd) != 1)
	{
		free_splits(pwd);
		ft_error(st, "pipex: could not get pwd!");
	}
	tname = ft_strtrim(name, ".");
	cmd = ft_strjoin(*pwd, tname);
	free_splits(pwd);
	free(tname);
	if (access(cmd, X_OK))
	{
		perror(name);
		free(cmd);
		ft_error(st, NULL);
	}
	return (cmd);
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
		ft_error(st, "pipex", name, "Command not found", NULL);
	return (cmd);
}

char	*get_cmd(t_pipex *st, char *name, char *env[])
{
	if (!name)
		return (NULL);
	if (ft_strnstr(name, "./", 2) == name)
		return (get_cmd_pwd(st, name, env));
	else
		return (get_cmd_path(st, name, env));
}

bool	init(t_pipex *st, char  *argv[], char *env[])
{
	if (access(argv[1], R_OK))
		perror(argv[1]);
	if (!access(argv[4], F_OK) && access(argv[4], W_OK))
		perror(argv[4]);
	st->fd1 = open(argv[1], O_RDONLY);
	st->fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	pipe(st->pipe);
	st->argv1 = ft_split(argv[2], ' ');
	st->argv2 = ft_split(argv[3], ' ');
	if (!st->argv1 || !st->argv2 || !st->argv1[0] || !st->argv2[0])
		ft_error(st, "pipex: No command specified.", NULL);
	st->cmd1 = get_cmd(st, st->argv1[0], env);
	st->cmd2 = get_cmd(st, st->argv2[0], env);
	st->env = env;
	return (true);
}

void	parent(t_pipex *st)
{
	dup2(st->pipe[1], STDOUT_FILENO); // redirect STDOUT to pipe input. close STDOUT, and dup st->pipe[1] to STDOUT
	dup2(st->fd1, STDIN_FILENO); // redirect stdin to infile
	close(st->pipe[0]);
	close(st->pipe[1]);
	close(st->fd1);
	close(st->fd2);
	execve(st->cmd1, st->argv1, st->env);
	perror("pipex");
}

void	child(t_pipex *st)
{
	dup2(st->pipe[0], STDIN_FILENO); // redirect STDIN to pipe output
	dup2(st->fd2, STDOUT_FILENO);
	close(st->pipe[0]);
	close(st->pipe[1]);
	close(st->fd1);
	close(st->fd2);
	execve(st->cmd2, st->argv2, st->env);
	perror("pipex");
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
		parent(&st);
	else
		child(&st);
	cleanup(&st);
	return (0);
}
