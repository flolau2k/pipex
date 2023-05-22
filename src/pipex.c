/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/05/22 10:30:30 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_arr(char **arr)
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
	free(st->argv1);
	free(st->argv2);
	
}

char	*get_env(char *env[], char *key)
{
	int		i;

	if (ft_strlen(key) == 0)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], key, ft_strlen(key)))
			return (env[i]);
		++i;
	}
	return (NULL);
}

void	get_cmd(t_pipex *st, char *env[])
{
	char	**path;

	path = ft_split(env);
}

bool	init(t_pipex *st, char  *argv[], char *env[])
{
	if (access(argv[1], R_OK))
		return (false);
	if (!access(argv[4], F_OK) && access(argv[4], W_OK))
		return (false);
	st->fd1 = open(argv[1], O_RDONLY);
	st->fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 644);
	pipe(st->pipe);
	st->argv1 = ft_split(argv[2], ' ');
	st->argv2 = ft_split(argv[3], ' ');
	if (!st->argv2)
		return (free_arr(st->argv1), false);
	get_cmd(st, env);
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
	cleanup(st);
}

void	child(t_pipex *st)
{
	close(st->pipe[1]);
	dup2(st->pipe[0], STDIN_FILENO); // redirect STDIN to pipe output
	dup2(st->fd2, STDOUT_FILENO);
	execve(st->cmd2, st->argv2, st->env);
	perror(strerror(errno));
	cleanup(st);
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
		return (perror(strerror(errno)), -1);
	st.pid = fork();
	if (st.pid)
		parent(&st);
	else
		child(&st);
	return (0);
}
