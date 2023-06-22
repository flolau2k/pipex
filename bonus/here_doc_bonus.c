/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:27:25 by flauer            #+#    #+#             */
/*   Updated: 2023/06/22 14:59:44 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child(int *pipe, char *lim)
{
	char	*line;

	close(pipe[0]);
	line = get_next_line(STDIN_FILENO);
	while (ft_strnstr(line, lim, ft_strlen(lim)) != line)
	{
		ft_putstr_fd(line, pipe[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(pipe[0]);
	close(pipe[1]);
	exit(0);
}

void	here_doc_pipe(char *lim)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror("pipex: pipe");
	pid = fork();
	if (pid == -1)
		ft_errp("fork");
	if (pid == 0)
		child(pipe_fd, lim);
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		wait(NULL);
	}
}

void	here_doc(int argc, char *argv[])
{
	int	outfile;

	if (argc < 6)
		ft_err(ft_strdup(ERRMSG_HD));
	outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (outfile == -1)
		ft_errp(argv[argc - 1]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	here_doc_pipe(argv[2]);
}
