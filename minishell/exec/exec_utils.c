/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:30:45 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/16 11:30:52 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

char	*find_loop(char	**paths, char	*path_no_cmd, char *cmd)
{
	char	*path;
	size_t	i;

	path = NULL;
	i = 0;
	while (paths[i])
	{
		if (!(cmd[0] == '.' && cmd [1] == '/') && cmd[0] != '/')
		{
			path_no_cmd = ft_strjoin(paths[i], "/");
			if (!path_no_cmd)
				return (free_array(paths), free(path), NULL);
			path = ft_strjoin(path_no_cmd, cmd);
			if (!path)
				return (free(path_no_cmd), free_array(paths), NULL);
			if (access(path, X_OK) == 0)
				return (path);
		}
		else
			if (access(cmd, X_OK) == 0)
				return (cmd);
		i++;
	}
	return (free_array(paths), free(path), NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_no_cmd;
	size_t	i;

	path_no_cmd = NULL;
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (find_loop(paths, path_no_cmd, cmd));
}

int	execute(char **cmd, char **envp)
{
	char	*path;

	if (!cmd)
		return (0);
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_dprintf(2, "\e[1;37m%s\e[0m : Command not found\n", cmd[0]);
		return (free_array(cmd), 127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_dprintf(2, "\e[1;37m%s\e[0m : Command not found\n", cmd[0]);
		free_array(cmd);
		free(path);
		return (0);
	}
	return (1);
}
