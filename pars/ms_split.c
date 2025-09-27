/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:10:36 by authomas          #+#    #+#             */
/*   Updated: 2025/09/27 15:07:55 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	skip_quote(char *str, int index)
{
	if (str[index] == '\'')
	{
		index++;
		while (str[index] && str[index] != '\'')
			index++;
	}
	else if (str[index] == '\"')
	{
		index++;
		while (str[index] && str[index] != '\"')
			index++;
	}
	return (index);
}

static size_t	count_token(char *input_str, char *separator)
{
	size_t	i;
	size_t	nbr_token;
	int		new_token;

	i = 0;
	nbr_token = 0;
	new_token = 1;
	while (input_str[i])
	{
		if (input_str[i] == '\'' || input_str[i] == '\"')
		{
			i = skip_quote(input_str, i);
			if (!input_str[i])
				return (0);
		}
		if (new_token && !ft_strchr(separator, input_str[i]))
		{
			nbr_token++;
			new_token = 0;
		}
		if (ft_strchr(separator, input_str[i]))
			new_token = 1;
		i++;
	}
	return (nbr_token);
}

static size_t	token_len(char *input_str, char *separator)
{
	size_t	i;

	i = 0;
	while (input_str[i] && !ft_strchr(separator, input_str[i]))
	{
		if (input_str[i] == '\'' || input_str[i] == '\"')
			i = skip_quote(input_str, i);
		i++;
	}
	return (i);
}

static int	fill_token(char **token_lst, char *input_str,
				char *separator, size_t nbr_token)
{
	size_t	j;
	size_t	i;
	size_t	len_token;

	j = 0;
	while (j < nbr_token)
	{
		i = 0;
		while (input_str && ft_strchr(separator, *input_str))
			input_str++;
		len_token = token_len(input_str, separator);
		token_lst[j] = ft_calloc(sizeof(char), (len_token + 1));
		if (!token_lst[j])
			return (0);
		while (i < len_token)
		{
			token_lst[j][i] = (*input_str);
			input_str++;
			i++;
		}
		token_lst[j][i] = '\0';
		j++;
	}
	token_lst[j] = NULL;
	return (1);
}

char	**ms_split(char *input_str, char *separator)
{
	char	**token_lst;
	size_t	nbr_token;

	nbr_token = count_token(input_str, separator);
	if (!nbr_token)
		return (NULL);
	token_lst = ft_calloc(sizeof(char *), (nbr_token + 2));
	if (!token_lst)
		return (NULL);
	if (!fill_token(token_lst, input_str, separator, nbr_token))
	{
		free_array(token_lst);
		return (NULL);
	}
	return (token_lst);
}
