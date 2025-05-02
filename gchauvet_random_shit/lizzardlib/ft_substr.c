/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:56:49 by gchauvet          #+#    #+#             */
/*   Updated: 2025/04/29 16:58:19 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;

	i = 0;
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - (start);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	ss = ft_calloc(len + 1, sizeof(char));
	if (ss == NULL)
		return (NULL);
	while (i < len && s[i])
	{
		ss[i] = s[start + i];
		i++;
	}
	return (ss);
}
