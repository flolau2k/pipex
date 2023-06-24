/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:57:22 by flauer            #+#    #+#             */
/*   Updated: 2023/06/23 15:24:26 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_infile(char *file)
{
	int	infile;

	infile = open(file, O_RDONLY);
	if (infile == -1)
		ft_errp(file);
	dup2(infile, STDIN_FILENO);
	close(infile);
}

void	open_outfile(char *file, bool here_doc)
{
	int	outfile;

	if (here_doc)
		outfile = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		outfile = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfile == -1)
		ft_errp(file);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
}
