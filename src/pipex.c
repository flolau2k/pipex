/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:31:28 by flauer            #+#    #+#             */
/*   Updated: 2023/05/12 12:10:51 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv)
{
	// create a data structure: 
	t_pipex	st;

	// input to be expected:
	// 4 arguments: infile cmd1 cmd2 outfile
	if (argc != 5)
		return (perror("Argument Error"), ERRRET);
	
	// check and process args
	if (access(argv[1], R_OK) || access(argv[4], W_OK))
		return (perror(strerr(errno)), ERRRET);~
	st.fd1 = open(argv[1], O_RDONLY);
	st.fd2 = open(argv[4], O_WRONLY);
	st.cmd1 = argv[2];
	st.cmd2 = argv[3];
	
	// create a pipe
	// call the first command and make it output to the write end of the pipe
	// call the second command and make it read from the read end of the pipe
	// and output to the file outfile.
}
