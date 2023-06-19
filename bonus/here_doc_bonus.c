/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:27:25 by flauer            #+#    #+#             */
/*   Updated: 2023/06/19 16:21:52 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child(int *pipe, char *argv[])
{
	char	*lim;
	char	*line;

	lim = argv[2];
	close(pipe[0]);
	line = get_next_line(STDIN_FILENO);
	while (ft_strnstr(line, lim, ft_strlen(lim)) != line)
	{
		ft_putstr_fd(line, pipe[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	exit(0);
}

void	here_doc(char *argv[])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror("pipex: pipe");
	pid = fork();
	if (pid == -1)
		ft_errp("fork");
	if (pid == 0)
		child(pipe_fd, argv);
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		wait(NULL);
	}
}
