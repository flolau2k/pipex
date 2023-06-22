/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/06/22 09:29:39 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char *name, char *env[])
{
	if (!name)
		return (NULL);
	if (name[0] == '/' || ft_strnstr(name, "./", 2) == name)
		return (ft_strdup(name));
	else
		return (get_cmd_path(name, env));
}

void	execute(char **args, char **env)
{
	char	*msg;
	char	*cmd_msg;
	char	*cmd;

	cmd = get_cmd(args[0], env);
	if (!cmd)
	{
		cmd_msg = ft_strjoin("command not found: ", args[0]);
		free_splits(args);
		ft_err(cmd_msg);
	}
	if (execve(cmd, args, env) == -1)
	{
		cmd_msg = ft_strjoin(cmd, ": ");
		msg = ft_strjoin(cmd_msg, strerror(errno));
		free(cmd_msg);
		free(cmd);
		free_splits(args);
		ft_err(msg);
	}
}

void	child(int *pipe, char **argv, char **env)
{
	int		file;
	char	**args;

	file = open(argv[1], O_RDONLY);
	if (file == -1)
		ft_errp(argv[1]);
	dup2(pipe[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	args = ft_split(argv[2], ' ');
	execute(args, env);
}

void	parent(int *pipe, char **argv, char **env)
{
	int		file;
	char	**args;

	file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file == -1)
		ft_errp(argv[4]);
	dup2(pipe[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	args = ft_split(argv[3], ' ');
	execute(args, env);
}

int	main(int argc, char *argv[], char *env[])
{
	pid_t	pid;
	int		pipefd[2];

	if (argc != 5)
		return (write(STDERR_FILENO, ERRMSG, 51));
	if (pipe(pipefd) == -1)
		ft_errp("pipex: pipe");
	pid = fork();
	if (pid == -1)
		ft_errp("pipex: fork");
	if (pid)
		parent(pipefd, argv, env);
	else
		child(pipefd, argv, env);
	return (0);
}
