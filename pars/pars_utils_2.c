/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:20:49 by authomas          #+#    #+#             */
/*   Updated: 2025/09/10 18:48:16 by authomas         ###   ########lyon.fr   */
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
		if (input[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	unexpected_token(t_data *data)
{
	data->exit_code = 2;
	ft_dprintf(2, "Error: unexpected token\n");
	return (0);
}

int	is_code(char *token, char **value, int *key_len, t_data *data)
{
	if (token[1] == '?')
	{
		*value = ft_itoa(data->exit_code);
		if (!*value)
			return (0);
		*key_len = 2;
		return (1);
	}
	return (0);
}

int	permission_denied(int fd, char *name, t_data *data)
{
	if (fd == -1)
	{
		ft_dprintf(2, "\e[1;37m%s\e[0m : permission denied", name);
		data->exit_code = 1;
		free(name);
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
