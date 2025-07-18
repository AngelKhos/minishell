/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/17 16:34:09 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

char	*convert_part_to_arg(t_data *data, int index)
{
	int		i;
	char	*cmd_plus_arg;

	cmd_plus_arg = NULL;
	i = 0;
	while (i < data->cmd[index].len)
	{
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, " ");
		if (!cmd_plus_arg)
			return (NULL);
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, data->cmd[index].parts[i].str);
		if (!cmd_plus_arg)
			return (NULL);
		i++;
	}
	return (cmd_plus_arg);
}

void	redir_file(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index)
{
	if (cmd_index == 0 && data->cmd[cmd_index].infile != -1)
	{
		dup2(data->cmd[cmd_index].infile, STDIN_FILENO);
		close(pr_pip[0]);
		close(pr_pip[1]);
	}
	if (cmd_index == data->nb_pipes && data->cmd[cmd_index].outfile != -1)
	{
		dup2(data->cmd[cmd_index].outfile, STDOUT_FILENO);
		close(cur_pip[0]);
		close(cur_pip[1]);
	}
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

	cmd_str = convert_part_to_arg(data, cmd_index);
	curr_pipe[0] = -1;
	curr_pipe[1] = -1;
	if (data->nb_pipes > 0)
		pipe(curr_pipe);
	pids[cmd_index] = fork();
	if (pids[cmd_index] == 0)
	{
		redir_file(data, prev_pipe, curr_pipe, cmd_index);
		redir_pipe(data, prev_pipe, curr_pipe, cmd_index);
		close_child_pipe(prev_pipe, curr_pipe);
		execute(cmd_str, tree_to_envp(data->env));
		exit(0);
	}
	if (data->nb_pipes > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
	}
	free(cmd_str);
}

void	read_cmd(t_data *data)
{
	int		cmd_index;
	int		prev_pipes[2];
	int		*pids;

	cmd_index = 0;
	pids = ft_calloc(sizeof(int), data->nb_pipes + 1);
	prev_pipes[0] = -1;
	prev_pipes[1] = -1;
	if (data->nb_pipes > 0)
		pipe(prev_pipes);
	while (cmd_index <= data->nb_pipes)
	{
		read_cmd_if(data, cmd_index, prev_pipes, pids);
		cmd_index++;
	}
	cmd_index = 0;
	while (cmd_index <= data->nb_pipes)
	{
		waitpid(pids[cmd_index], NULL, 0);
		cmd_index++;
	}
	read_cmd_end_close(data, prev_pipes);
	close_redir(data);
	free(pids);
}
