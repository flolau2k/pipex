/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:26:21 by flauer            #+#    #+#             */
/*   Updated: 2023/06/27 16:16:40 by flauer           ###   ########.fr       */
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
# define ERRMSG "Usage: pipex infile \"cmd1\" \"cmd2\" ... \"cmdx\" outfile\n"
# define ERRMSG_HD "Usage: pipex here_doc LIMITER cmd cmd1 file"

// see https://tldp.org/LDP/abs/html/exitcodes.html
# define CMD_ERROR 126
# define CMD_NOT_FOUND 127
# define GENERAL_ERROR 1

typedef struct s_args
{
	int		i;
	int		argc;
	char	**argv;
	char	**env;
	bool	here_doc;
}	t_args;

// pipex_bonus.c
void	execute(char *args, char **env);
void	check_args(int argc, char **argv, t_args *args);
void	pipex(t_args *args, int *stat_loc);
int		main(int argc, char *argv[], char *env[]);

// utils_bonus.c
void	free_splits(char **arr);
char	**get_env(char *env[], char *key);
char	*get_cmd_path(char *name, char *env[]);
char	*get_cmd(char *name, char *env[]);

// here_doc_bonus.c
void	hd_child(void *arg);
void	here_doc(t_args *args);

// pipe_functions_bonus.c
pid_t	create_pipe(void (f1)(void *), void *a1);
void	first_child(void *arg);
void	generic_child(void *arg);

// file_utils.c
void	open_infile(char *file);
void	open_outfile(char *file, bool here_doc);

// errors_bonus.c
void	print_usage(void);
void	ft_errp(char *msg);
void	ft_err(char *msg, int retval);

#endif
