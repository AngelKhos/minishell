/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:30:45 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/09 17:38:57 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

char	*find_loop_while(char **paths, char *cmd)
{
	char	*path;
	char	*path_no_cmd;
	size_t	i;

	path = NULL;
	i = 0;
	path_no_cmd = NULL;
	while (paths[i])
	{
		path_no_cmd = ft_strjoin(paths[i], "/");
		if (!path_no_cmd)
			return (free_array(paths), NULL);
		path = ft_strjoin(path_no_cmd, cmd);
		free(path_no_cmd);
		if (!path)
			return (free_array(paths), NULL);
		if (access(path, X_OK) == 0)
			return (free_array(paths), path);
		free(path);
		i++;
	}
	return (free_array(paths), NULL);
}

char	*find_loop(char	**paths, char *cmd)
{
	if (!(cmd[0] == '.' && cmd [1] == '/') && cmd[0] != '/')
	{
		return (find_loop_while(paths, cmd));
	}
	else
		if (access(cmd, X_OK) == 0)
			return (cmd);
	return (free_array(paths), NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	size_t	i;
	char	*path;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (envp[i])
		paths = ft_split(envp[i] + 5, ':');
	else
		paths = ft_split(".", ':');
	if (!paths)
		return (NULL);
	path = find_loop(paths, cmd);
	return (path);
}

int	execute(char **cmd, char **envp)
{
	char	*path;

	if (!cmd)
		return (free_array(envp), 0);
	if (!*cmd)
	{
		free(cmd);
		free_array(envp);
		return (1);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_dprintf(2,
			"\e[1;37m%s\e[0m : Command not found\n",
			cmd[0]);
		free_array(envp);
		return (free_array(cmd), 127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_array(envp);
		free_array(cmd);
		free(path);
		return (0);
	}
	return (1);
}
