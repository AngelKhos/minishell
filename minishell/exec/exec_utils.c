/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:30:45 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/04 20:59:44 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <stdlib.h>

char	*find_loop(char	**paths, char	*path_no_cmd, char *cmd)
{
	char	*path;
	size_t	i;

	path = NULL;
	i = 0;
	while (paths[i])
	{
		path_no_cmd = ft_strjoin(paths[i], "/");
		if (!path_no_cmd)
			return (free_array(paths), free(path), NULL);
		// if (path)
			//free(path);
		path = ft_strjoin(path_no_cmd, cmd);
		if (!path)
			return (free(path_no_cmd), free_array(paths), NULL); 
		//free(path_no_cmd);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	write(2, "invalid command\n", 16);
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

int	execute(char *cmd_arg, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = NULL;
	cmd = ft_split(cmd_arg, ' ');
	if (!cmd)
		return (0);
	path = find_path(cmd[0], envp);
	if (!path)
		return (free_array(cmd), 0);
	if (execve(path, cmd, envp) == -1)
	{
		free_array(cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
	return (0);
}