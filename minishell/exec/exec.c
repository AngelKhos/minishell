/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/11 16:08:26 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <sys/wait.h>

char	*convert_part_to_arg(t_data *data, t_cmd *cmd, int index)
{
	int		size;
	int		i;
	char	*cmd_plus_arg;

	(void)data;
	cmd_plus_arg = NULL;
	i = 0;
	size = 1;
	while (cmd[0].parts[index + size].type == ARG)
		size++;
	while (i < size)
	{
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, " ");
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, cmd[0].parts[i].str);
		i++;
	}
	return (cmd_plus_arg);
}

void	redir_pipe(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index)
{
	if (data->nb_pipes > 0)
	{
		if (cmd_index > 0)
		{
			dup2(pr_pip[0], STDIN_FILENO);
			close(pr_pip[0]);
			close(pr_pip[1]);
		}
		if (cmd_index < data->nb_pipes)
		{
			dup2(cur_pip[1], STDOUT_FILENO);
			close(cur_pip[0]);
			close(cur_pip[1]);
		}
	}
}

void	exec_cmd(t_data *data, int prev_pipe[2], int *pids, int cmd_index)
{
	int		curr_pipe[2];
	char	*cmd_str;

	cmd_str = convert_part_to_arg(data, data->cmd + cmd_index, 0);
	pipe(curr_pipe);
	pids[cmd_index] = fork();
	if (pids[cmd_index] == 0)
	{
		redir_pipe(data, prev_pipe, curr_pipe, cmd_index);
		execute(cmd_str, data->envp);
		exit(0);
	}
	if (cmd_index > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	prev_pipe[0] = curr_pipe[0];
	prev_pipe[1] = curr_pipe[1];
	free(cmd_str);
}

void	read_cmd(t_data *data)
{
	int		cmd_index;
	int		prev_pipes[2];
	int		*pids;

	cmd_index = 0;
	pids = malloc(sizeof(int) * data->nb_pipes + 1);
	pipe(prev_pipes);
	while (cmd_index <= data->nb_pipes)
	{
		exec_cmd(data, prev_pipes, pids, cmd_index);
		cmd_index++;
	}
	cmd_index = 0;
	while (cmd_index <= data->nb_pipes)
	{
		waitpid(pids[cmd_index], NULL, 0);
		cmd_index++;
	}
	free(pids);
}
