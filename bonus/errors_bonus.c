/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:03:34 by flauer            #+#    #+#             */
/*   Updated: 2023/06/26 15:56:39 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_usage(void)
{
	ft_printf("%s\n", "pipex: input error");
	ft_printf("%s\n", "usage: pipex [infile|here_doc LIMITER] \
infile cmd1 cmd2 ... cmdn outfile");
	exit(GENERAL_ERROR);
}

void	ft_errp(char *msg)
{
	char	*message;

	if (msg)
	{
		message = ft_strjoin("pipex: ", msg);
		perror(message);
		free(message);
	}
	else
		perror("pipex: ");
	exit(GENERAL_ERROR);
}

void	ft_err(char *msg, int retval)
{
	char	*message;

	message = ft_strjoin("pipex: ", msg);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	free(message);
	free(msg);
	exit(retval);
}
