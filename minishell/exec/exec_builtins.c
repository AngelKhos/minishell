/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:16:49 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/03 18:24:08 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <sys/wait.h>

void    builtins_if(t_data *data, int cmd_index)
{
    char *str;

    str = data->cmd[cmd_index].parts[0].str;
    if (ft_strncmp(str, "cd", -1) == 0)
    {
        cd(data, data->cmd[cmd_index].parts[1].str);
    }
    else if (ft_strncmp(str, "pwd", -1) == 0)
    {
        pwd(data);
    }
    else if (ft_strncmp(str, "env", -1) == 0)
    {
        env(data);
    }
    else if (ft_strncmp(str, "exit", -1) == 0)
    {
        exit_minishell_edition(data, "exit");
    }
    else if (ft_strncmp(str, "echo", -1) == 0)
    {
        echo(data->cmd[cmd_index]);
    }
}

int     need_fork(char *buil)
{
    if (ft_strncmp(buil, "cd", -1) == 0)
    {
        return (0);
    }
    else if (ft_strncmp(buil, "pwd", -1) == 0)
    {
        return (1);
    }
    else if (ft_strncmp(buil, "env", -1) == 0)
    {
        return (1);
    }
    else if (ft_strncmp(buil, "exit", -1) == 0)
    {
        return (0);
    }
    else if (ft_strncmp(buil, "echo", -1) == 0)
    {
        return (1);
    }
    return (1);
}

void exec_in_parent(t_data *data, int cmd_index, int prev_pipe[2])
{
    if (need_fork(data->cmd[cmd_index].parts[0].str) == 0)
    {
        builtins_if(data, cmd_index);
        if (data->nb_pipes <= 0)
        {
            close(prev_pipe[0]);
		    close(prev_pipe[1]);
            return ;
        }
    }
}

void	exec_builtins(t_data *data, int prev_pipe[2], int *pids, int cmd_index)
{
	int		curr_pipe[2];

	curr_pipe[0] = -1;
	curr_pipe[1] = -1;
    exec_in_parent(data, cmd_index, prev_pipe);
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
