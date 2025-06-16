/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:08:14 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/16 16:59:52 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	exit_minishell_edition(t_data *data)
{
	free_data(data);
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}