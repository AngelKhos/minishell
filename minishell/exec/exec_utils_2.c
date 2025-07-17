/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:23:30 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/17 16:03:37 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/data.h"

void	close_child_pipe(int prev_pipe[2], int curr_pipe[2])
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (curr_pipe[0] != -1)
	{
		close(curr_pipe[0]);
		close(curr_pipe[1]);
	}
}

void	read_cmd_if(t_data *data, int cmd_index, int prev_pipes[2], int *pids)
{
	if (data->cmd[cmd_index].parts[0].type == CMD)
	{
		exec_cmd(data, prev_pipes, pids, cmd_index);
	}
	else if (data->cmd[cmd_index].parts[0].type == BUIL)
	{
		if (is_exit_or_cd(data, cmd_index) == 1 && data->nb_pipes < 1)
		{
			builtins_if(data, cmd_index);
		}
		else
		{
			exec_builtins(data, prev_pipes, pids, cmd_index);
		}
	}
}

void	read_cmd_end_close(t_data *data, int prev_pipe[2])
{
	if (data->nb_pipes > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
}
