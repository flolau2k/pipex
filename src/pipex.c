/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/06/17 12:30:38 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char *name, char *env[])
{
	char	*cmd;

	cmd = NULL;
	if (!name)
		return (NULL);
	if (name[0] == '/' || ft_strnstr(name, "./", 2) == name)
		return (ft_strdup(name));
	else
		return (get_cmd_path(name, env));
}

void	child(int *pipe, char **argv, char **env)
{
	char	*msg;
	int		file;
	char	**args;
	char	*cmd;

	file =  open(argv[1], O_RDONLY);
	if (file == -1)
		ft_errp(argv[1]);
	dup2(pipe[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	args = ft_split(argv[2], ' ');
	cmd = get_cmd(args[0], env);
	if (execve(cmd, args, env) == -1)
	{
		msg = strerror(errno);
		free(cmd);
		free(args);
		ft_err(msg);
	}
}

void	parent(int *pipe, char **argv, char **env)
{
	char	*msg;
	int		file;
	char	**args;
	char	*cmd;

	file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file == -1)
		ft_errp(argv[4]);
	dup2(pipe[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	args = ft_split(argv[3], ' ');
	cmd = get_cmd(args[0], env);
	if (execve(cmd, args, env) == -1)
	{
		msg = strerror(errno);
		free(cmd);
		free(args);
		ft_err(msg);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	pid_t	pid;
	int		pipefd[2];
	int		stat;

	if (argc != 5)
		return (write(STDERR_FILENO, ERRMSG, 51));
	if (pipe(pipefd) == -1)
		perror("pipex: pipe:");
	if ((pid = fork()) == -1)
		perror("pipex: fork");
	if (pid)
	{
		waitpid(pid, NULL, 0);
		if (WIFEXITED(stat) && WEXITSTATUS(stat) == 0)
			parent(pipefd, argv, env);
	}
	else
		child(pipefd, argv, env);
	return (WEXITSTATUS(stat));
}
