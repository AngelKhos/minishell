/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:48:51 by authomas          #+#    #+#             */
/*   Updated: 2025/08/16 11:06:52 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintnbr(int fd, int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_dprintstr(fd, "-2147483648"));
	if (n < 0)
	{
		i += ft_dprintchar(fd, '-');
		n = -n;
	}
	if (n >= 10)
		i += ft_dprintnbr(fd, n / 10);
	return (i + ft_dprintchar(fd, n % 10 + '0'));
}

int	ft_dprintunbr(int fd, unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 10)
		i = ft_dprintunbr(fd, n / 10);
	return (i + ft_dprintchar(fd, n % 10 + '0'));
}
