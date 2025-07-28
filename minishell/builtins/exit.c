/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:08:14 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/28 15:12:13 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <unistd.h>

int		is_num(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_body(t_data *data, t_cmd *cmd, int *code)
{
	if (!is_num(cmd->parts[1].str))
	{
		ft_printf("exit: %s: numeric argument required\n", cmd->parts[1].str);
		*code = 2;
		data->run = 0;
	}
	else
	{
		*code = ft_atoi(cmd->parts[1].str);
		data->run = 0;
	}
	if (*code != 2)
	{
		if (cmd && cmd->len > 2)
		{
			ft_printf("exit: too many arguments\n", cmd->parts[1].str);
			*code = 1;
			data->run = 1;
		}
	}
}

int		exit_minishell_edition(t_data *data, t_cmd *cmd)
{
	int	code;

	code = 0;
	ft_printf("exit\n");
	if (cmd && cmd->len > 1)
	{
		exit_body(data, cmd, &code);
	}
	else
	{
		data->run = 0;
	}
	return (code);
}
