/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:40:46 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/09 17:24:36 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	free_cmd(t_data *data)
{
	int	i_part;
	int	i_cmd;

	i_cmd = 0;
	while (i_cmd <= data->nb_pipes)
	{
		i_part = 0;
		while (i_part < data->cmd[i_cmd].len)
		{
			free(data->cmd[i_cmd].parts[i_part].str);
			i_part++;
		}
		free(data->cmd[i_cmd].parts);
		i_cmd++;
	}
	free(data->cmd);
}

void	free_data(t_data *data)
{
	if (data->curent_path)
		free(data->curent_path);
	tree_destroy(data->env);
	free(data);
}

void	close_here_doc(t_cmd *cmd)
{
	if (cmd->here_doc == 1)
	{
		close(cmd->infile);
		unlink(cmd->hd_name);
		free(cmd->hd_name);
	}
}

void	close_file(t_data *data)
{
	int		i_cmd;
	t_cmd	*cmd;

	i_cmd = 0;
	while (i_cmd <= data->nb_pipes)
	{
		cmd = &data->cmd[i_cmd];
		if (cmd->infile != -1)
			close(cmd->infile);
		if (cmd->outfile != -1)
			close(cmd->outfile);
		close_here_doc(cmd);
		i_cmd++;
	}
}
