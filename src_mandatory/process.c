/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:48:21 by abrecio-          #+#    #+#             */
/*   Updated: 2025/12/02 11:05:51 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	create_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	execute_first_command(char **argv, int *pipe_fd, char **envp)
{
	int	fd_input;

	fd_input = open_input_file(argv[1]);
	if (fd_input != -1)
	{
		dup2(fd_input, STDIN_FILENO);
		close(fd_input);
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_command(argv[2], envp);
}

void	execute_second_command(char **argv, int *pipe_fd, char **envp)
{
	int	fd_output;

	fd_output = open_output_file(argv[4]);
	if (fd_output != -1)
	{
		dup2(fd_output, STDOUT_FILENO);
		close(fd_output);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_command(argv[3], envp);
}
