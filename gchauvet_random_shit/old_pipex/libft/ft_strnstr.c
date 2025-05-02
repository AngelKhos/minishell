/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:45:11 by ********          #+#    #+#             */
/*   Updated: 2024/11/26 13:36:28 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (i < len && big[i])
	{
		i2 = 0;
		if (big[i] == little[i2])
		{
			while (big[i + i2] == little[i2] && (i + i2) < len)
			{
				i2++;
				if (little[i2] == 0)
					return (&((char *)big)[i]);
			}
		}
		i++;
	}
	return (NULL);
}
