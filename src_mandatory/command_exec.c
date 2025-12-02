/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:47:18 by abrecio-          #+#    #+#             */
/*   Updated: 2025/11/25 15:58:15 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	handle_command_not_found(char **cmd_args)
{
	write(2, "Command not found: ", 19);
	write(2, cmd_args[0], ft_strlen(cmd_args[0]));
	write(2, "\n", 1);
	free_array(cmd_args);
	exit(127);
}

static void	exec_command(char *path, char **cmd_args, char **envp)
{
	if (execve(path, cmd_args, envp) == -1)
	{
		perror("execve");
		free(path);
		free_array(cmd_args);
		exit(EXIT_FAILURE);
	}
}

void	execute_command(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	if (!cmd || !*cmd)
	{
		write(2, "Command not found: empty\n", 25);
		exit(127);
	}
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		write(2, "Command not found: empty\n", 25);
		if (cmd_args)
			free_array(cmd_args);
		exit(127);
	}
	path = find_command_path(cmd_args[0], envp);
	if (!path)
		handle_command_not_found(cmd_args);
	exec_command(path, cmd_args, envp);
}
