/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:16:49 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/01 11:09:28 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <sys/wait.h>

int	builtins_if(t_data *data, int cmd_index)
{
	char	*str;
	int		code;

	code = 0;
	str = data->cmd[cmd_index].parts[0].str;
	if (ft_strncmp(str, "cd", -1) == 0)
		code = cd(data, data->cmd[cmd_index]);
	if (ft_strncmp(str, "pwd", -1) == 0)
		code = pwd(data);
	if (ft_strncmp(str, "env", -1) == 0)
		code = env(data, cmd_index);
	if (ft_strncmp(str, "exit", -1) == 0)
		code = exit_minishell_edition(data, &data->cmd[cmd_index]);
	if (ft_strncmp(str, "echo", -1) == 0)
		code = echo(data->cmd[cmd_index]);
	if (ft_strncmp(str, "export", -1) == 0)
		code = ft_export(data, &data->cmd[cmd_index]);
	if (ft_strncmp(str, "unset", -1) == 0)
		code = unset(data, cmd_index);
	return (code);
}

int	is_exit_or_cd(t_data *data, int cmd_index)
{
	char	*str;

	str = data->cmd[cmd_index].parts[0].str;
	if (ft_strncmp(str, "exit", -1) == 0)
		return (1);
	if (ft_strncmp(str, "cd", -1) == 0)
		return (1);
	if (ft_strncmp(str, "export", -1) == 0)
		return (1);
	if (ft_strncmp(str, "unset", -1) == 0)
		return (1);
	return (0);
}

int	exec_builtins(t_data *data, int prev_pipe[2], int *pids, int cmd_index)
{
	int	curr_pipe[2];

	curr_pipe[0] = -1;
	curr_pipe[1] = -1;
	if (data->nb_pipes > 0)
		if (pipe(curr_pipe) == -1)
			return (0);
	g_pid = fork();
	if (g_pid == -1)
		return (close_pipe_in_exec_cmd(prev_pipe, curr_pipe), 0);
	if (g_pid == 0)
	{
		redir_pipe(data, prev_pipe, curr_pipe, cmd_index);
		redir_file(data, prev_pipe, curr_pipe, cmd_index);
		close_child_pipe(prev_pipe, curr_pipe);
		close_redir(data);
		exit(builtins_if(data, cmd_index));
	}
	else if (g_pid > 0)
		pids[cmd_index] = g_pid;
	if (data->nb_pipes > 0)
		close_pipe_in_exec_cmd(prev_pipe, curr_pipe);
	return (1);
}
