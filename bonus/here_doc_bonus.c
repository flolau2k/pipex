/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:27:25 by flauer            #+#    #+#             */
/*   Updated: 2023/06/27 16:17:52 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	hd_child(void *arg)
{
	char	*line;
	char	*lim;

	lim = ft_strjoin((char *)arg, "\n");
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, lim, ft_strlen(lim)))
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(lim);
	exit(0);
}

void	here_doc(t_args *args)
{
	if (args->argc < 6)
		print_usage();
	create_pipe(&hd_child, args->argv[2]);
	wait(NULL);
}
