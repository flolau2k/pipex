/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:52:47 by flauer            #+#    #+#             */
/*   Updated: 2023/06/27 16:16:44 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

pid_t	create_pipe(void (f1)(void *), void *a1)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_errp("pipex: pipe");
	pid = fork();
	if (pid == -1)
		ft_errp("pipex: fork");
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (f1)
			f1(a1);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (pid);
}

void	first_child(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	open_infile(args->argv[1]);
	generic_child(arg);
}

void	generic_child(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	execute(args->argv[args->i], args->env);
}
