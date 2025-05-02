/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:43:03 by gchauvet          #+#    #+#             */
/*   Updated: 2025/04/29 16:58:19 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ns;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	ns = ft_calloc((len + 1), sizeof(char));
	if (ns == NULL)
		return (0);
	while (i < len)
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
