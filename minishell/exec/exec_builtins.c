/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:16:49 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/24 15:18:49 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <sys/wait.h>

void	builtins_if(t_data *data, int cmd_index)
{
	char	*str;

	str = data->cmd[cmd_index].parts[0].str;
	if (ft_strncmp(str, "cd", -1) == 0)
		data->exit_code = cd(data, data->cmd[cmd_index]);
	if (ft_strncmp(str, "pwd", -1) == 0)
		data->exit_code = pwd(data);
	if (ft_strncmp(str, "env", -1) == 0)
		data->exit_code = env(data);
	if (ft_strncmp(str, "exit", -1) == 0)
		exit_minishell_edition(data, "exit");
	if (ft_strncmp(str, "echo", -1) == 0)
		data->exit_code = echo(data->cmd[cmd_index]);
	if (ft_strncmp(str, "export", -1) == 0)
		data->exit_code = ft_export(data, data->cmd[cmd_index].parts[1].str);
	if (ft_strncmp(str, "unset", -1) == 0)
		data->exit_code = unset(data, cmd_index);
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

void	exec_builtins(t_data *data, int prev_pipe[2], int *pids, int cmd_index)
{
	int	curr_pipe[2];

	curr_pipe[0] = -1;
	curr_pipe[1] = -1;
	if (data->nb_pipes > 0)
		pipe(curr_pipe);
	pids[cmd_index] = fork();
	if (pids[cmd_index] == 0)
	{
		redir_pipe(data, prev_pipe, curr_pipe, cmd_index);
		close_child_pipe(prev_pipe, curr_pipe);
		builtins_if(data, cmd_index);
		exit(0);
	}
	if (data->nb_pipes > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
	}
}
