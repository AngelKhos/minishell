/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/15 15:12:08 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	read_cmd(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i <= cmd->len)
	{
		if (cmd->parts[i].type == CMD)
		{
			// exec cmd
			// check the PIPE and ARG in this if
		}
		else if (cmd->parts[i].type == HEREDOC)
		{
			// here doc
		}
		i++;
	}
}