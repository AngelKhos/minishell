/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:15:14 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/24 15:17:08 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	unset(t_data *data, int cmd_index)
{
	tree_remove(&data->env, data->cmd[cmd_index].parts[1].str);
	return (0);
}
