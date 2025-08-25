/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/25 11:39:41 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

char	**convert_part_to_arg(t_data *data, int index)
{
	int		i;
	char	**cmd;

	cmd = ft_calloc(sizeof(char *), data->cmd[index].len + 1);
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < data->cmd[index].len)
	{
		cmd[i] = ft_strdup(data->cmd[index].parts[i].str);
		if (!cmd[i])
		{
			free_array(cmd);
			return (NULL);
		}
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	close_pipe_in_exec_cmd(int prev_pipe[2], int curr_pipe[2])
{
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	prev_pipe[0] = curr_pipe[0];
	prev_pipe[1] = curr_pipe[1];
}

int	exec_cmd(t_data *data, int prev_pipe[2], int *pids, int cmd_index)
{
	int		curr_pipe[2];
	int		child_return;

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
		child_return = child_proc(data, prev_pipe, curr_pipe, cmd_index);
		if (child_return == 0)
			ft_dprintf(2, "Error in child\n");
		exit(127);
	}
	else if (g_pid > 0)
		pids[cmd_index] = g_pid;
	if (data->nb_pipes > 0)
		close_pipe_in_exec_cmd(prev_pipe, curr_pipe);
	return (1);
}

int	read_cmd(t_data *data)
{
	int		cmd_index;
	int		prev_pipe[2];
	int		*pids;

	cmd_index = 0;
	pids = ft_calloc(sizeof(int), data->nb_pipes + 1);
	if (!pids)
		return (0);
	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	if (data->nb_pipes > 0)
	{
		if (pipe(prev_pipe) == -1)
			return (free(pids), 0);
	}
	while (cmd_index <= data->nb_pipes)
	{
		if (read_cmd_if(data, cmd_index, prev_pipe, pids) == 0)
			ft_dprintf(2, "Exec error\n");
		cmd_index++;
	}
	wait_all(data, pids);
	read_cmd_end_close(data, prev_pipe);
	close_redir(data);
	return (free(pids), 1);
}
