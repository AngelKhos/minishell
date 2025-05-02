/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:06:36 by ********          #+#    #+#             */
/*   Updated: 2024/11/26 14:03:10 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_strndup(const char *s, size_t n)
{
	char	*ns;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	ns = ft_calloc((n + 1), sizeof(char));
	if (ns == NULL)
		return (0);
	while (i < len && i < n)
	{
		ns[i] = s[i];
		i++;
	}
	return (ns);
}

static size_t	wordcount(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			nb++;
		i++;
	}
	return (nb);
}

static void	freearray(char ***array)
{
	size_t	i;

	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

static void	cpyword(char ***array, char const *s, char c)
{
	size_t	i;
	size_t	i2;
	size_t	len;

	i = 0;
	i2 = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		len = i;
		while (s[i] && s[i] != c)
			i++;
		if (len < i)
		{
			(*array)[i2] = ft_strndup(s + len, i - len);
			if ((*array)[i2] == NULL)
			{
				freearray(array);
				return ;
			}
			i2++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;

	i = 0;
	array = ft_calloc(wordcount(s, c) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	cpyword(&array, s, c);
	return (array);
}
