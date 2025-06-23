/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:07:03 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/23 15:17:53 by gchauvet         ###   ########.fr       */
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
		{
			close(data->cmd[cmd_index].outfile);
			if (data->cmd[cmd_index].here_doc == 1)
				unlink(".here_doc.tmp");
		}
		cmd_index++;
	}
}