/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:10:52 by abrecio-          #+#    #+#             */
/*   Updated: 2025/11/25 17:10:53 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

void	execute_first_command(char **argv, int *pipe_fd, char **envp);
void	execute_second_command(char **argv, int *pipe_fd, char **envp);
void	create_pipe(int *pipe_fd);
void	close_pipe(int *pipe_fd);
void	execute_command(char *cmd, char **envp);
char	*find_command_path(char *cmd, char **envp);
char	*get_path_from_env(char **envp);
int		open_input_file(char *filename);
int		open_output_file(char *filename);
void	free_array(char **arr);
void	execute_child(char *cmd, int input_fd, int output_fd, char **envp);
void	read_heredoc(char *limiter, int write_fd);

#endif
