/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:26:21 by flauer            #+#    #+#             */
/*   Updated: 2023/06/17 13:59:16 by flauer           ###   ########.fr       */
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
# define ERRMSG "Input Error: expected infile \"cmd1\" \"cmd2\" outfile\n"

char	*get_cmd(char *name, char *env[]);
void	child(int *pipe, char **argv, char **env);
void	parent(int *pipe, char **argv, char **env);
// int		main(int argc, char *argv[], char *env[]);

void	free_splits(char **arr);
char	**get_env(char *env[], char *key);
void	ft_errp(char *msg);
void	ft_err(char *msg);
char	*get_cmd_path(char *name, char *env[]);

#endif
