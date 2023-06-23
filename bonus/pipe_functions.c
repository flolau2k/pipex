/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:52:47 by flauer            #+#    #+#             */
/*   Updated: 2023/06/23 15:54:09 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

pid_t	create_pipe(
			void (f1)(int *, void *),
			void *a1,
			void (f2)(int *, void *),
			void *a2)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_errp("pipex: pipe");
	pid = fork();
	if (pid == -1)
		ft_errp("pipex: fork");
	if (pid == 0)
		f1(pipe_fd, a1);
	else
		f2(pipe_fd, a2);
	return (pid);
}

void	first_child(int *pipe_fd, void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	open_infile(args->argv[1]);
	generic_child(pipe_fd, arg);
}

void	generic_child(int *pipe_fd, void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(args->argv[args->i], args->env);
}

void	generic_parent(int *pipe_fd, void *arg)
{
	(void)arg;
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
