/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:07:03 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/20 11:10:09 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	close_redir(t_data *data)
{
	int		cmd_index;

	cmd_index = 0;
	while (cmd_index <= data->nb_pipes)
	{
		if (data->cmd[cmd_index].infile != -1)
			close(data->cmd[cmd_index].infile);
		if (data->cmd[cmd_index].outfile != -1)
			close(data->cmd[cmd_index].outfile);
		if (data->cmd[cmd_index].here_doc == 1)
			unlink(".here_doc.tmp");
		cmd_index++;
	}
}

void	redir_file(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index)
{
	if (cmd_index == 0 && data->cmd[cmd_index].infile != -1)
	{
		dup2(data->cmd[cmd_index].infile, STDIN_FILENO);
		close(pr_pip[0]);
		close(pr_pip[1]);
		close(data->cmd[cmd_index].infile);
	}
	if (cmd_index == data->nb_pipes && data->cmd[cmd_index].outfile != -1)
	{
		dup2(data->cmd[cmd_index].outfile, STDOUT_FILENO);
		close(cur_pip[0]);
		close(cur_pip[1]);
		close(data->cmd[cmd_index].outfile);
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
