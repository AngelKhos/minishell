/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:15:49 by ********          #+#    #+#             */
/*   Updated: 2024/11/26 14:05:37 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(char *a, char *b)
{
	char	t;

	t = *a;
	*a = *b;
	*b = t;
}

static void	rev(char *s)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(s);
	while (i < size / 2)
	{
		ft_swap(&s[i], &s[(size - 1) - i]);
		i++;
	}
}

static size_t	callen(int n)
{
	size_t	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*fills(char *s, int n)
{
	size_t	i;

	i = 0;
	while (n != 0)
	{
		s[i] = (((unsigned)n % 10) + '0');
		n /= 10;
		i++;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		negative;
	char	*s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	negative = 0;
	if (n < 0)
	{
		negative = 1;
		n = n * -1;
	}
	len = callen(n);
	s = ft_calloc((len + negative + 1), sizeof(char));
	if (!s)
		return (NULL);
	s = fills(s, n);
	if (negative == 1)
		s[ft_strlen(s)] = '-';
	rev(s);
	return (s);
}
