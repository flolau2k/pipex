/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:26:21 by flauer            #+#    #+#             */
/*   Updated: 2023/06/19 15:56:21 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/include/libft.h"
# define ERRMSG "Usage: ./pipex infile \"cmd1\" \"cmd2\" ... \"cmdx\" outfile\n"
# define ERRMSG_HD "Usage: ./pipex here_doc LIMITER cmd cmd1 file"

char	*get_cmd(char *name, char *env[]);
int		main(int argc, char *argv[], char *env[]);

void	free_splits(char **arr);
char	**get_env(char *env[], char *key);
void	ft_errp(char *msg);
void	ft_err(char *msg);
char	*get_cmd_path(char *name, char *env[]);

void	here_doc(char *argv[], char *env[]);
void	child(int *pipe, char *argv[], char *env[]);

#endif
