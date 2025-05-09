/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:00:27 by authomas          #+#    #+#             */
/*   Updated: 2024/11/26 16:23:01 by authomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	mc_len;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	mc_len = ft_strlen(s + start);
	if (mc_len >= len)
		mc_len = len;
	str = ft_calloc(sizeof(char), mc_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < mc_len)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}
