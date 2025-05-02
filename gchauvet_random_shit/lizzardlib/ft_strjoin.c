/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:27:21 by gchauvet          #+#    #+#             */
/*   Updated: 2025/04/29 16:58:19 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	i;

	if (!s1)
	{
		s = ft_strdup(s2);
		if (!s)
			return (NULL);
		return (s);
	}
	s = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	i = -1;
	if (s == NULL)
		return (NULL);
	while (s1[++i])
		s[i] = s1[i];
	while (s2[i - ft_strlen(s1)])
	{
		s[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	free(s1);
	return (s);
}
