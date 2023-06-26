/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:11:02 by flauer            #+#    #+#             */
/*   Updated: 2023/06/26 14:11:58 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(void)
{
	ft_printf("%s\n", "pipex: input error");
	ft_printf("%s\n", "usage: pipex infile cmd1 cmd2 outfile");
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
		perror("pipex");
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
