/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:20:49 by authomas          #+#    #+#             */
/*   Updated: 2025/09/13 23:18:41 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	is_exp(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			i = skip_quote(input, i);
		if (!input[i])
			break ;
		if (input[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	unexpected_token(int type, t_data *data)
{
	data->exit_code = 2;
	if (type == 1)
		ft_dprintf(2, "Error: unexpected token\n");
	if (type == 2)
		ft_dprintf(2, "Error: invalid arguments near token '|'\n");
	return (0);
}

int	permission_denied(int type, char *name, t_data *data)
{
	if (access(name, F_OK) != 0)
	{
		ft_dprintf(2, "\e[1;37m%s\e[0m : no such file or directory\n", name);
		free(name);
		data->exit_code = 1;
		return (1);
	}
	if (access(name, R_OK) != 0 && type == 1)
	{
		ft_dprintf(2, "\e[1;37m%s\e[0m : permission denied\n", name);
		free(name);
		data->exit_code = 1;
		return (1);
	}
	if (access(name, W_OK) != 0 && type == 2)
	{
		ft_dprintf(2, "\e[1;37m%s\e[0m : permission denied\n", name);
		free(name);
		data->exit_code = 1;
		return (1);
	}
	return (0);
}

int	checking_missing_command(char *input)
{
	int		i;
	char	*str;

	str = ft_strtrim(input, " \r\t\v\f");
	if (!str || str[0] == '|')
	{
		free(str);
		return (0);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
					|| str[i] == '\r' || str[i] == '\f'))
				i++;
			if (!str[i] || str[i] == '|')
				return (free(str), 0);
		}
		i++;
	}
	free(str);
	return (1);
}
