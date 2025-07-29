/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:07:06 by authomas          #+#    #+#             */
/*   Updated: 2025/07/28 15:26:57 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	env(t_data *data, int cmd_index)
{
	if (data->cmd[cmd_index].len > 1)
	{
		ft_printf("\e[1;37menv\e[0m: too many arguments\n");
		return (1);
	}
	print_tree(data->env);
	return (0);
}
