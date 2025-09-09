/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:15:14 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/08 23:14:07 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	unset(t_data *data, int cmd_index)
{
	int	i;

	i = 1;
	if (!data->env)
	{
		ft_dprintf(2, "unset: env not set\n");
		return (1);
	}
	if (data->cmd[cmd_index].len < 2)
		return (0);
	while(i < data->cmd[cmd_index].len)
	{
		tree_remove(&data->env, data->cmd[cmd_index].parts[i].str);
		i++;
	}
	return (0);
}
