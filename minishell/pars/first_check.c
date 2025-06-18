/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:27:21 by authomas          #+#    #+#             */
/*   Updated: 2025/06/18 20:32:30 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int checking_missing_command(char *input)
{
	int i;
	char *str;

	str = ft_strtrim(input, " \r\t\v\f");
	if (!str || str[0] == '|')
	{
		free(str);
		return (0);
	}
	i = 0;
	while(str[i])
	{	
		if (str[i] == '|')
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' 
				|| str[i] == '\r' || str[i] == '\f'))
				i++;
			if (!str[i])
				return (0);
			if (str[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int check_quote(char *input, char quote)
{
	int i;
	i = 0;

	while (input[i])
	{
		if (input[i] == quote)
		{
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
					return (0);
			i++;
		}
		i++;
	}
	return (1);
}

int first_check(char *input)
{
    
	if (!checking_missing_command(input))
    {
        return (0);
    }
    if (!check_quote(input, '"'))
    {
        return (0);
    }
	if (!check_quote(input, '\''))
	{
		return (0);
	}
    return (1);
}