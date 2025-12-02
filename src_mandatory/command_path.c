/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:46:07 by abrecio-          #+#    #+#             */
/*   Updated: 2025/11/25 15:46:39 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*path_join(char *dir, char *file)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, file);
	free(temp);
	return (result);
}

static char	*search_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = path_join(paths[i], cmd);
		if (!full_path)
		{
			free_array(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_path_from_env(envp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(cmd, paths));
}
