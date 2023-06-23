// void	first_pipe(pid_t pid, int *pipe_fd, char *infile, char *cmd, char **env)
// {
// 	if (pid)
// 	{
// 		dup2(pipe_fd[0], STDIN_FILENO);
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 	}
// 	else
// 	{
// 		open_file(infile);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		execute(cmd, env);
// 	}
// }

// void	normal_pipe(pid_t pid, int *pipe_fd, char *cmd, char **env)
// {
// 	if (pid)
// 	{
// 		dup2(pipe_fd[0], STDIN_FILENO);
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 	}
// 	else
// 	{
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		execute(cmd, env);
// 	}
// }

// pid_t	create_pipe(int i, char **args, char **env)
// {
// 	pid_t	pid;
// 	int		pipe_fd[2];

// 	if (pipe(pipe_fd) == -1)
// 		ft_errp("pipex: pipe");
// 	pid = fork();
// 	if (pid == -1)
// 		ft_errp("pipex: fork");
// 	if (pid)
// 	{
// 		dup2(pipe_fd[0], STDIN_FILENO);
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 	}
// 	else
// 	{
// 		if (i == 2)
// 			open_file(args[1]);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		execute(args[i], env);
// 	}
// 	return (pid);
// }

int main(int argc, char *argv[], char *env[])
{
	int		i;
	int		outfile;
	pid_t	pid;
	int		pipe_fd[2];

	i = 3;
	if (argc < 5)
		return (write(STDERR_FILENO, ERRMSG, 62), 127);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		here_doc(argc, argv);
	pid = create_pipe(pipe_fd);
	first_pipe(pid, pipe_fd, argv[1], argv[2], env);
	while (i < argc - 2)
	{
		pid = create_pipe(pipe_fd);
		normal_pipe(pid, pipe_fd, argv[i], env);
		++i;
	}
	
}

// int	main(int argc, char *argv[], char *env[])
// {
// 	if (argc < 5)
// 		return (print_usage(), 127);
// 	if (ft_strncmp("here_doc", argv[1], 8) == 0)
// 		here_doc(argc, argv, env);
// 	else
// 		pipex(argc, argv, env);
// 	return (0);
// }

// int	main(int argc, char *argv[], char *env[])
// {
// 	int		i;
// 	bool	is_here_doc;

// 	i = 2;
// 	if (argc < 5)
// 		return (write(STDERR_FILENO, ERRMSG, 62), 127);
// 	if (is_here_doc = ft_strncmp("here_doc", argv[1], 8) == 0)
// 	{
// 		here_doc(argc, argv);
// 		i = 3;
// 	}
// 	t_child cargs;
// 	cargs.cmd = argv[2];
// 	cargs.infile = argv[1];
// 	cargs.env = env;
// 	create_pipe(&first_child, &cargs, &generic_parent, NULL);
// 	while (i < argc - 2)
// 	{
// 		cargs.cmd = argv[i];
// 		create_pipe(&generic_child, &cargs, &generic_parent, NULL);
// 		++i;
// 	}
// 	if (!here_doc)
// 		open_outfile(argv[argc - 1], false);
// 	execute(argv[argc - 2], env);
// 	return (0);
// }


// void	here_doc(int argc, char *argv[], char *env[])
// {
// 	int		i;
// 	t_child	args;

// 	args.cmd = argv[2];
// 	args.infile = argv[1];
// 	args.env = env;
// 	if (argc < 6)
// 		ft_err(ft_strdup(ERRMSG_HD));
// 	open_outfile(argv[argc - 1], true);
// 	create_pipe(&hd_child, &argv[2], &generic_parent, NULL);
// 	wait(NULL);
// 	i = 3;
// 	while (i < argc - 2)
// 	{
// 		args.cmd = argv[i];
// 		create_pipe(&generic_child, &args, &generic_parent, NULL);
// 		++i;
// 	}
// 	execute(argv[argc - 2], env);
// }
