/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:42:46 by abrecio-          #+#    #+#             */
/*   Updated: 2025/12/02 12:42:53 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_child(char *cmd, int input_fd, int output_fd, char **envp)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	execute_command(cmd, envp);
}

void	handle_multiple_pipes(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		prev_fd;
	int		i;
	pid_t	pid;
	int		out_fd;

	prev_fd = open_input_file(argv[1]);
	if (prev_fd == -1)
		exit(EXIT_FAILURE);
	i = 2;
	while (i < argc - 2)
	{
		create_pipe(pipe_fd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			close(pipe_fd[0]);
			execute_child(argv[i], prev_fd, pipe_fd[1], envp);
		}
		close(pipe_fd[1]);
		close(prev_fd);
		prev_fd = pipe_fd[0];
		i++;
	}
	out_fd = open_output_file(argv[argc - 1]);
	if (out_fd == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		execute_child(argv[i], prev_fd, out_fd, envp);
	close(prev_fd);
	close(out_fd);
	while (wait(NULL) > 0)
		;
}

void	read_heredoc(char *limiter, int write_fd)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (ft_strncmp(line, limiter, limiter_len) == 0 
			&& line[limiter_len] == '\n')
		{
			free(line);
			break;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
}

void	execute_heredoc_commands(char **argv, int pipe_fd, char **envp)
{
	int		pipe_fd2[2];
	pid_t	pid2;
	int		out_fd;

	create_pipe(pipe_fd2);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		close(pipe_fd2[0]);
		dup2(pipe_fd, STDIN_FILENO);
		close(pipe_fd);
		dup2(pipe_fd2[1], STDOUT_FILENO);
		close(pipe_fd2[1]);
		execute_command(argv[3], envp);
	}
	close(pipe_fd);
	close(pipe_fd2[1]);
	out_fd = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd == -1)
		exit(EXIT_FAILURE);
	dup2(pipe_fd2[0], STDIN_FILENO);
	close(pipe_fd2[0]);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	waitpid(pid2, NULL, 0);
	execute_command(argv[4], envp);
}

void	handle_heredoc(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 6)
	{
		write(2, "Usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n", 48);
		exit(1);
	}
	create_pipe(pipe_fd);
	read_heredoc(argv[2], pipe_fd[1]);
	close(pipe_fd[1]);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		execute_heredoc_commands(argv, pipe_fd[0], envp);
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc < 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 47);
		write(2, "   or: ./pipex here_doc LIMITER cmd1 cmd2 file\n", 48);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		handle_heredoc(argc, argv, envp);
	else
		handle_multiple_pipes(argc, argv, envp);
	return (0);
}
