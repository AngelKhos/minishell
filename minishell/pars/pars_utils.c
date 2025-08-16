/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:20:01 by authomas          #+#    #+#             */
/*   Updated: 2025/08/16 11:24:43 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

char *strdup_wquotes(char *s)
{
	size_t	i;
	size_t	j;
	char	*dest;
	int quote_flag;

	quote_flag = 0;
	dest = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' && quote_flag != 2)
		{
			if(quote_flag == 1)
				quote_flag = 0;
			if(quote_flag == 0)
				quote_flag = 1;
		}
		else if (s[i] == '\"' && quote_flag != 1)
		{
			if(quote_flag == 2)
				quote_flag = 0;
			if(quote_flag == 0)
				quote_flag = 2;
		}
		else
		{
			dest[j] = s[i];
			j++;
		}
		i++;
	}
	free(s);
	return (dest);
}