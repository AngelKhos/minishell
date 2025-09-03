/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:20:01 by authomas          #+#    #+#             */
/*   Updated: 2025/09/03 18:32:35 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

static void	strdup_wquotes_while(char *s, int *quote_flag,
	size_t i[2], char *dest)
{
	while (s[i[0]])
	{
		if (s[i[0]] == '\'' && (*quote_flag) != 2)
		{
			if ((*quote_flag) == 1)
				(*quote_flag) = 0;
			if ((*quote_flag) == 0)
				(*quote_flag) = 1;
		}
		else if (s[i[0]] == '\"' && (*quote_flag) != 1)
		{
			if ((*quote_flag) == 2)
				(*quote_flag) = 0;
			if ((*quote_flag) == 0)
				(*quote_flag) = 2;
		}
		else
		{
			dest[i[1]] = s[i[0]];
			i[1]++;
		}
		i[0]++;
	}
}

char	*strdup_wquotes(char *s)
{
	size_t	i[2];
	char	*dest;
	int		quote_flag;

	quote_flag = 0;
	dest = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	strdup_wquotes_while(s, &quote_flag, i, dest);
	return (free(s), dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dest;

	if (n < ft_strlen(s))
		dest = malloc(sizeof(char) * (n + 1));
	else
		dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_builtins(char *input)
{
	char	*str;

	str = input;
	if (ft_strncmp(str, "cd", -1) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", -1) == 0)
		return (1);
	if (ft_strncmp(str, "env", -1) == 0)
		return (1);
	if (ft_strncmp(str, "exit", -1) == 0)
		return (1);
	if (ft_strncmp(str, "echo", -1) == 0)
		return (1);
	if (ft_strncmp(str, "export", -1) == 0)
		return (1);
	if (ft_strncmp(str, "unset", -1) == 0)
		return (1);
	return (0);
}
