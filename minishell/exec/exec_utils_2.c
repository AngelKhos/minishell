/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:23:30 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/16 11:31:11 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/data.h"
#include <sys/wait.h>

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

int	read_cmd_if(t_data *data, int cmd_index, int prev_pipes[2], int *pids)
{
	if (data->cmd[cmd_index].parts[0].type == CMD)
	{
		if (exec_cmd(data, prev_pipes, pids, cmd_index) == 0)
			return (0);
	}
	else if (data->cmd[cmd_index].parts[0].type == BUIL)
	{
		if (is_exit_or_cd(data, cmd_index) == 1 && data->nb_pipes < 1)
		{
			data->exit_code = builtins_if(data, cmd_index);//same here
		}
		else
		{
			exec_builtins(data, prev_pipes, pids, cmd_index);//same here
		}
	}
	return (1);
}

void	read_cmd_end_close(t_data *data, int prev_pipe[2])
{
	if (data->nb_pipes > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
}

void	wait_all(t_data *data, int *pids)
{
	int		cmd_index;
	int		code;

	code = 0;
	cmd_index = data->nb_pipes;
	while (cmd_index >= 0)
	{
		if (pids[cmd_index] > 0)
		{
			waitpid(pids[cmd_index], &code, 0);
			data->exit_code = code >> 8;
			if ((code >> 8) == 127)
				ft_dprintf(2, "\e[1;37m%s\e[0m : Command not found\n", data->cmd[cmd_index].parts->str);
		}
		cmd_index--;
	}
	g_pid = 0;
	
}

int	child_porc(t_data *data, int prev_pipe[2], int curr_pipe[2], int cmd_i)
{
	char	**cmd;

	cmd = convert_part_to_arg(data, cmd_i);
	redir_file(data, prev_pipe, curr_pipe, cmd_i);
	redir_pipe(data, prev_pipe, curr_pipe, cmd_i);
	close_child_pipe(prev_pipe, curr_pipe);
	return (execute(cmd, tree_to_envp(data->env)));
}
