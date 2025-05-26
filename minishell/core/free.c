/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:40:46 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/26 14:39:31 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <stdlib.h>

static void	free_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->cmd->len)
	{
		if (data->cmd->parts[i].str)
			free(data->cmd->parts[i].str);
		i++;
	}
	free(data->cmd->parts);
	if (data->cmd->infile)
		free(data->cmd->infile);
	if (data->cmd->outfile)
		free(data->cmd->outfile);
	free(data->cmd);
}

void free_data(t_data *data)
{
	if (data->curent_path)
		free(data->curent_path);
	if (data->input)
		free(data->input);
	if (data->cmd)
		free_cmd(data);
}