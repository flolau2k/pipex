/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/06/27 10:07:30 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *arg, char **env)
{
	char	*msg;
	char	*cmd_msg;
	char	*cmd;
	char	**args;

	args = ft_split(arg, ' ');
	cmd = get_cmd(args[0], env);
	if (!cmd)
	{
		cmd_msg = ft_strjoin("command not found: ", args[0]);
		free_splits(args);
		ft_err(cmd_msg, CMD_NOT_FOUND);
	}
	if (execve(cmd, args, env) == -1)
	{
		cmd_msg = ft_strjoin(cmd, ": ");
		msg = ft_strjoin(cmd_msg, strerror(errno));
		free(cmd_msg);
		free(cmd);
		free_splits(args);
		ft_err(msg, CMD_ERROR);
	}
}

void	child(int *pipe, char **argv, char **env)
{
	int		file;

	file = open(argv[1], O_RDONLY);
	if (file == -1)
		ft_errp(argv[1]);
	dup2(pipe[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	execute(argv[2], env);
}

void	parent(int *pipe, char **argv, char **env)
{
	int		file;

	file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file == -1)
		ft_errp(argv[4]);
	dup2(pipe[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	execute(argv[3], env);
}

void	check_args(int argc, char **argv)
{
	char	**args;
	int		i;

	i = 2;
	if (argc != 5)
		print_usage();
	while (i < 4)
	{
		args = ft_split(argv[i], ' ');
		if (!args || !args[0])
		{
			free_splits(args);
			print_usage();
		}
		free_splits(args);
		++i;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	pid_t	pid;
	int		pipe_fd[2];

	check_args(argc, argv);
	if (pipe(pipe_fd) == -1)
		ft_errp("pipex: pipe");
	pid = fork();
	if (pid == -1)
		ft_errp("pipex: fork");
	if (pid)
		parent(pipe_fd, argv, env);
	else
		child(pipe_fd, argv, env);
	return (0);
}
