/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/06/21 21:16:12 by flauer           ###   ########.fr       */
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

void	execute(char *cmd, char *args[], char *env[])
{
	char	*msg;
	char	*cmd_msg;
	char	*path;

	path = get_cmd(cmd, env);
	if (!path)
	{
		cmd_msg = ft_strjoin("command not found: ", cmd);
		ft_err(cmd_msg);
	}
	if (execve(path, args, env) == -1)
	{
		cmd_msg = ft_strjoin(path, ": ");
		msg = ft_strjoin(cmd_msg, strerror(errno));
		free(cmd_msg);
		free(path);
		ft_err(msg);
	}
}

pid_t	create_pipe(char *cmd, char *args[], char *env[])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror("pipex: pipe");
	pid = fork();
	if (pid == -1)
	{
		perror("pipex: fork");
		exit(127);
	}
	if (pid)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	else
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute(cmd, args, env);
	}
	return (pid);
}

int	main(int argc, char *argv[], char *env[])
{
	int		infile;
	int		outfile;
	char	**args;

	if (argc != 5)
		return (write(STDERR_FILENO, ERRMSG, 51));
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		ft_errp(argv[1]);
	dup2(infile, STDIN_FILENO);
	args = ft_split(argv[2], ' ');
	// check args here!
	create_pipe(args[0], args, env);
	outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfile == -1)
		ft_errp(argv[4]);
	dup2(outfile, STDOUT_FILENO);
	free_splits(args);
	args = ft_split(argv[3], ' ');
	// check args here!
	execute(args[0], args, env);
	return (0);
}
