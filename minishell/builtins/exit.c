/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:08:14 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/29 11:13:32 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <unistd.h>

int	ft_exit_atoi(char *s)
{
	int			i;
	long		res;
	int			sign;

	res = 0;
	i = 0;
	sign = 1;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if ((res * sign) > 2147483647)
			return (2);
		i++;
	}
	if (res > 255)
		return ((res * sign) % 256);
	return (res * sign);
}

int		is_num(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

void	exit_body(t_data *data, t_cmd *cmd, int *code)
{
	if (!is_num(cmd->parts[1].str))
	{
		*code = 2;
		data->run = 0;
	}
	else
	{
		*code = ft_exit_atoi(cmd->parts[1].str);
		data->run = 0;
	}
	if (*code != 2)
	{
		if (cmd && cmd->len > 2)
		{
			ft_printf("\e[1;37mexit\e[0m: too many arguments\n", cmd->parts[1].str);
			*code = 1;
			data->run = 1;
		}
	}
	else
		ft_printf("\e[1;37mexit\e[0m: \e[1;37m%s\e[0m: numeric argument required\n", cmd->parts[1].str);
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
		code = data->exit_code;
		data->run = 0;
	}
	return (code);
}
