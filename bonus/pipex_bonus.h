/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:26:21 by flauer            #+#    #+#             */
/*   Updated: 2023/06/23 14:56:33 by flauer           ###   ########.fr       */
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

typedef struct s_args
{
	int		i;
	int		argc;
	char	**argv;
	char	**env;
}	t_args;

// pipex_bonus.c
void	execute(char *args, char **env);
int		main(int argc, char *argv[], char *env[]);
void	open_outfile(char *file, bool here_doc);

// utils_bonus.c
void	free_splits(char **arr);
char	**get_env(char *env[], char *key);
char	*get_cmd_path(char *name, char *env[]);
char	*get_cmd(char *name, char *env[]);

// here_doc_bonus.c
void	hd_child(int *pipe_fd, void *arg);
void	here_doc_pipe(char *lim);
void	here_doc(t_args *args);

// pipe_functions.c
pid_t	create_pipe(
			void (f1)(int *, void *),
			void *a1,
			void (f2)(int *, void *),
			void *a2);
void	first_child(int *pipe_fd, void *arg);
void	generic_child(int *pipe_fd, void *arg);
void	generic_parent(int *pipe_fd, void *arg);

// file_utils.c
void	open_infile(char *file);
void	open_outfile(char *file, bool here_doc);

// errors.c
void	print_usage(void);
void	ft_errp(char *msg);
void	ft_err(char *msg);

#endif
