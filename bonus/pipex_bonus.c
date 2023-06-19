/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/06/19 12:21:55 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_cmd(char *name, char *env[])
{
	if (!name)
		return (NULL);
	if (name[0] == '/' || ft_strnstr(name, "./", 2) == name)
		return (ft_strdup(name));
	else
		return (get_cmd_path(name, env));
}

void	execute(char *args, char **env)
{
	char	*msg;
	char	*cmd_msg;
	char	*cmd;
	char	**args_split;

	args_split = ft_split(args, ' ');
	cmd = get_cmd(args_split[0], env);
	if (!cmd)
	{
		cmd_msg = ft_strjoin("command not found: ", args_split[0]);
		free_splits(args_split);
		ft_err(cmd_msg);
	}
	if (execve(cmd, args_split, env) == -1)
	{
		cmd_msg = ft_strjoin(cmd, ": ");
		msg = ft_strjoin(cmd_msg, strerror(errno));
		free(cmd_msg);
		free(cmd);
		free_splits(args_split);
		ft_err(msg);
	}
}

void	create_pipe(int i, char *argv[], char *env[])
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
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execute(argv[i], env);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int		i;
	int		file;

	i = 2;
	if (argc < 5)
		return (write(STDERR_FILENO, ERRMSG, 62), 127);
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		ft_errp(argv[1]);
	dup2(file, STDIN_FILENO);
	while (i < argc - 2)
	{
		create_pipe(i, argv, env);
		++i;
	}
	file = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file == -1)
		ft_errp(argv[argc - 1]);
	execute(argv[argc - 2], env);
	return (0);
}
