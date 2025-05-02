/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:16:27 by ********          #+#    #+#             */
/*   Updated: 2025/01/26 10:52:17 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_blen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		i++;
	}
	if (s[i] == '\n')
		i++;
	return (i);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*dup_s;
	int		i;

	dup_s = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s) + 1));
	if (dup_s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dup_s[i] = s[i];
		i++;
	}
	dup_s[i] = '\0';
	return (dup_s);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*new_s;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	new_s = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_blen(s2) + 1));
	if (new_s == NULL)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		new_s[i] = s1[i];
	j = 0;
	while (s2[j] && s2[j - 1] != '\n')
	{
		new_s[i] = s2[j];
		i++;
		j++;
	}
	new_s[i] = '\0';
	return (free(s1), new_s);
}

int	ft_strchr_gnl(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (1);
	return (0);
}
