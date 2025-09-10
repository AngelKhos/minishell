/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:36:08 by authomas          #+#    #+#             */
/*   Updated: 2024/11/16 08:21:46 by authomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*sourc;
	char		*dst;

	if (!dest && !src)
		return (0);
	i = 0;
	sourc = src;
	dst = dest;
	while (i < n)
	{
		dst[i] = sourc[i];
		i++;
	}
	return (dest);
}
