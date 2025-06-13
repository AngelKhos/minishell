/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:16:49 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/13 15:25:38 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <sys/wait.h>

void    builtins_if(t_data *data, int cmd_index)
{
    if (ft_strncmp(data->cmd[cmd_index].parts[0].str, "cd", -1) == 0)
    {
        cd(data, data->cmd[cmd_index].parts[1].str);
    }
    else if (ft_strncmp(data->cmd[cmd_index].parts[0].str, "pwd", -1) == 0)
    {
        pwd(data);
    }
    else if (ft_strncmp(data->cmd[cmd_index].parts[0].str, "env", -1) == 0)
    {
        //code for env
    }
    else if (ft_strncmp(data->cmd[cmd_index].parts[0].str, "exit", -1) == 0)
    {
        exit_minishell_edition(data);
    }
    else if (ft_strncmp(data->cmd[cmd_index].parts[0].str, "echo", -1) == 0)
    {
        //code for echo
    }
}

void	exec_builtins(t_data *data, int prev_pipe[2], int *pids, int cmd_index)
{
	int		curr_pipe[2];

	curr_pipe[0] = -1;
	curr_pipe[1] = -1;
	pipe(curr_pipe);
	pids[cmd_index] = fork();
	if (pids[cmd_index] == 0)
	{
		redir_pipe(data, prev_pipe, curr_pipe, cmd_index);
        builtins_if(data, cmd_index);
		exit(0);
	}
	if (cmd_index > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	prev_pipe[0] = curr_pipe[0];
	prev_pipe[1] = curr_pipe[1];
}