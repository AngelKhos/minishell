/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:15:14 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/08 18:41:00 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	unset(t_data *data, int cmd_index)
{
	if (!data->env)
	{
		ft_dprintf(2, "unset: env not set\n");
		return (1);
	}
	if (data->cmd[cmd_index].len < 2)
		return (0);
	tree_remove(&data->env, data->cmd[cmd_index].parts[1].str);
	return (0);
}
