/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:26:22 by gchauvet          #+#    #+#             */
/*   Updated: 2025/04/29 16:58:19 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	save;
	int		f;

	i = 0;
	f = 0;
	save = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			save = i;
			f = 1;
		}
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	if (f == 1)
		return ((char *)s + save);
	return (NULL);
}
