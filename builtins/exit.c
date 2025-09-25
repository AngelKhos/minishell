/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:08:14 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/25 14:47:16 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <unistd.h>

int	exit_atoi_while(size_t i, long *res, char *s, int sign)
{
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			(*res) = (*res) * 10 + (s[i] - '0');
			if (((*res) * sign) > 2147483647)
			{
				ft_dprintf(2,
					"exit : numeric argument required\n",
					s);
				return (2);
			}
			i++;
		}
		else
		{
			ft_dprintf(2,
				"exit : numeric argument required\n",
				s);
			return (2);
		}
	}
	return (0);
}

int	ft_exit_atoi(char *s)
{
	size_t		i;
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
	if (exit_atoi_while(i, &res, s, sign) == 2)
		return (2);
	if (res > 255)
		return ((res * sign) % 256);
	return (res * sign);
}

int	is_num(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57) && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

void	exit_body(t_data *data, t_cmd *cmd, int *code)
{
	if (!is_num(cmd->parts[1].str))
	{
		ft_dprintf(2,
			"exit : numeric argument required\n",
			cmd->parts[1].str);
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
			ft_dprintf(2,
				"\e[1;37mexit\e[0m: too many arguments\n",
				cmd->parts[1].str);
			*code = 1;
			data->run = 1;
		}
	}
}

int	exit_minishell_edition(t_data *data, t_cmd *cmd)
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
