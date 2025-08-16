/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:07:06 by authomas          #+#    #+#             */
/*   Updated: 2025/08/16 11:32:24 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	env(t_data *data, int cmd_index)
{
	if (data->cmd[cmd_index].len > 1)
	{
		ft_dprintf(2, "\e[1;37menv\e[0m: too many arguments\n");
		return (1);
	}
	print_tree(data->env);
	return (0);
}
