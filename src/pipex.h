/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:26:21 by flauer            #+#    #+#             */
/*   Updated: 2023/05/17 16:47:19 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/include/libft.h"

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	*cmd2;
	char	**argv1;
	char	**argv2;
	int		pipe[2];
	int		pid;
	char	**env;
}	t_pipex;

int		main(int argc, char *argv[], char *env[]);

void	child(t_pipex *st);

#endif
