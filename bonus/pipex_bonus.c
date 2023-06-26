/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/06/26 15:02:32 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute(char *args, char **env)
{
	char	*msg;
	char	*cmd_msg;
	char	*cmd;
	char	**args_split;

	args_split = ft_split(args, ' ');
	cmd = get_cmd(args_split[0], env);
	if (!cmd)
	{
		cmd_msg = ft_strjoin("command not found: ", args_split[0]);
		free_splits(args_split);
		ft_err(cmd_msg, CMD_NOT_FOUND);
	}
	if (execve(cmd, args_split, env) == -1)
	{
		cmd_msg = ft_strjoin(cmd, ": ");
		msg = ft_strjoin(cmd_msg, strerror(errno));
		free(cmd_msg);
		free(cmd);
		free_splits(args_split);
		ft_err(msg, CMD_ERROR);
	}
}

void	pipex(t_args *args)
{
	open_outfile(args->argv[args->argc - 1], false);
	create_pipe(&first_child, (void *)args, &generic_parent, NULL);
}

void	check_args(int argc, char **argv, t_args *args)
{
	int		i;
	char	**splits;

	i = 2;
	if (argc < 5)
		print_usage();
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		args->here_doc = true;
		++i;
	}
	while (i < argc - 1)
	{
		splits = ft_split(argv[i], ' ');
		if (!splits[0])
		{
			free_splits(splits);
			print_usage();
		}
		free_splits(splits);
		++i;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_args	args;

	args.here_doc = false;
	check_args(argc, argv, &args);
	args.i = 2;
	args.argc = argc;
	args.argv = argv;
	args.env = env;
	if (args.here_doc)
		here_doc(&args);
	else
		pipex(&args);
	args.i++;
	while (args.i < argc - 2)
	{
		create_pipe(&generic_child, (void *)&args, &generic_parent, NULL);
		args.i++;
	}
	execute(argv[argc - 2], env);
	return (0);
}
