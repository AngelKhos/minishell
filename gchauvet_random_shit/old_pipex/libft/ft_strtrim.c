/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:15:53 by ********          #+#    #+#             */
/*   Updated: 2024/11/20 00:20:48 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	left_sepa(char const *ts, size_t start, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (ts[start] == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	right_sepa(char const *ts, size_t end, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (ts[(ft_strlen(ts) - end) - 1] == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static void	cpyts(char *ts, size_t start, size_t end, char const *s1)
{
	size_t	i;

	i = 0;
	while (start + i < ft_strlen(s1) - end)
	{
		ts[i] = s1[start + i];
		i++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ts;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	ts = NULL;
	while (left_sepa(s1, start, set) != 0)
		if (left_sepa(s1, start, set) == 1)
			start++;
	while (right_sepa(s1, end, set) != 0)
		if (right_sepa(s1, end, set) == 1)
			end++;
	if (start == ft_strlen(s1) && end == ft_strlen(s1))
	{
		start /= 2;
		end /= 2;
	}
	ts = ft_calloc((ft_strlen(s1) - (start + end)) + 1, sizeof(char));
	if (ts == NULL)
		return (NULL);
	cpyts(ts, start, end, s1);
	return (ts);
}
