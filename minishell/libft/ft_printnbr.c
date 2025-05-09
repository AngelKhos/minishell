/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:48:51 by authomas          #+#    #+#             */
/*   Updated: 2025/01/27 17:10:09 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_printstr("-2147483648"));
	if (n < 0)
	{
		i += ft_printchar('-');
		n = -n;
	}
	if (n >= 10)
		i += ft_printnbr(n / 10);
	return (i + ft_printchar(n % 10 + '0'));
}

int	ft_printunbr(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 10)
		i = ft_printunbr(n / 10);
	return (i + ft_printchar(n % 10 + '0'));
}
