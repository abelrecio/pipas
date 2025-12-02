/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:48:18 by abrecio-          #+#    #+#             */
/*   Updated: 2025/12/02 11:09:12 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	handle_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (1);
}

static void	ft_pipex(char *argv[], char *envp[])
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	create_pipe(pipe_fd);
	pid1 = fork();
	if (!handle_error(pid1))
		exit(1);
	if (pid1 == 0)
		execute_first_command(argv, pipe_fd, envp);
	pid2 = fork();
	if (!handle_error(pid2))
		exit(1);
	if (pid2 == 0)
		execute_second_command(argv, pipe_fd, envp);
	close_pipe(pipe_fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		return (1);
	}
	ft_pipex(argv, envp);
	return (0);
}
