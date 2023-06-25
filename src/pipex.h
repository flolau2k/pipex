/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:26:21 by flauer            #+#    #+#             */
/*   Updated: 2023/06/25 17:27:53 by flauer           ###   ########.fr       */
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
# define ERRMSG "Usage: pipex infile \"cmd1\" \"cmd2\" outfile\n"

// see https://tldp.org/LDP/abs/html/exitcodes.html
# define CMD_ERROR 126
# define CMD_NOT_FOUND 127
# define GENERAL_ERROR 1

char	*get_cmd(char *name, char *env[]);
void	execute(char **args, char **env);
void	child(int *pipe, char **argv, char **env);
void	parent(int *pipe, char **argv, char **env);
int		main(int argc, char *argv[], char *env[]);

void	free_splits(char **arr);
char	**get_env(char *env[], char *key);
void	ft_errp(char *msg);
void	ft_err(char *msg, int retval);
char	*get_cmd_path(char *name, char *env[]);

#endif
