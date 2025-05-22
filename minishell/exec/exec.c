/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/18 17:13:50 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	read_cmd(t_data *data, t_cmd *cmd)
{
	int	i;
	int	have_pipe;
	int	nb_arg;

	i = 0;
	have_pipe = 0;
	nb_arg = 0;
	while (i <= cmd->len)
	{
		if (cmd->parts[i].type == CMD)
		{
			while (have_pipe == 0)
			{
				if (cmd->parts[i].type == PIPE)
					have_pipe = 1;
				if (cmd->parts[i].type == ARG)
					nb_arg++;
				i++;
			}
		}
		else if (cmd->parts[i].type == HEREDOC)
		{
			// here doc
		}
		i++;
	}
} // tu fais "while (++i <= cmd->len)" et tu set i a -1 au debut stv normer
