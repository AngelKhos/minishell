/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:40:46 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/20 11:21:54 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_cmd(t_data *data)
{
	int	i_part;
	int	i_cmd;

	i_cmd = 0;
	while (i_cmd <= data->nb_pipes)
	{
		i_part = 0;
		while (i_part <= data->cmd[i_cmd].len - 1)
		{
			if (data->cmd[i_cmd].parts[i_part].str)
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
