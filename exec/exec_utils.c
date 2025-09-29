/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:30:45 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/29 15:14:58 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	access_bin(char *path, int *code)
{
	int	r_code;

	r_code = 0;
	if (access(path, F_OK) == -1)
	{
		*code = 127;
		r_code = 1;
	}
	else if (access(path, X_OK) == -1)
	{
		*code = 126;
		r_code = 1;
	}
	return (r_code);
}

char	*find_loop_while(char **paths, char *cmd, int *code)
{
	char	*path;
	char	*path_no_cmd;
	size_t	i;

	path = NULL;
	i = -1;
	path_no_cmd = NULL;
	while (paths[++i])
	{
		path_no_cmd = ft_strjoin(paths[i], "/");
		if (!path_no_cmd)
			return (free_array_ptr(paths));
		(void)cmd;
		path = ft_strjoin(path_no_cmd, cmd);
		free(path_no_cmd);
		if (!path)
			return (free_array_ptr(paths));
		if (access_bin(path, code) == 0)
		{
			free_array(paths, 0);
			return (path);
		}
		free(path);
	}
	return (free_array_ptr(paths));
}

char	*find_loop(char	**paths, char *cmd, int *code)
{
	if (!(cmd[0] == '.' && cmd [1] == '/') && cmd[0] != '/' && cmd[0] != '.')
	{
		return (find_loop_while(paths, cmd, code));
	}
	else
	{
		if (access_bin(cmd, code) == 0)
		{
			free_array(paths, 0);
			return (cmd);
		}
	}
	free_array(paths, 0);
	return (NULL);
}

char	*find_path(char *cmd, char **envp, int *code)
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
	path = find_loop(paths, cmd, code);
	return (path);
}

int	execute(char **cmd, char **envp)
{
	char	*path;
	int		code;

	if (!cmd)
		return (free_array(envp, 0));
	if (!*cmd)
		return (free_more(cmd, envp, 1));
	code = 0;
	path = find_path(cmd[0], envp, &code);
	if (!path)
	{
		if (code == 127)
			ft_dprintf(2, "\e[1;37m%s\e[0m : Command not found\n", cmd[0]);
		if (code == 126)
			ft_dprintf(2, "\e[1;37m%s\e[0m : Permission denied\n", cmd[0]);
		free_array(envp, 0);
		return (free_array(cmd, code));
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_array(envp, 0);
		return (free_array(cmd, 0));
	}
	return (1);
}
