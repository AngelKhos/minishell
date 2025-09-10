/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:41:34 by authomas          #+#    #+#             */
/*   Updated: 2025/08/16 11:10:22 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintnbr_base(int fd, unsigned int n, char *base)
{
	unsigned int	len_base;
	int				i;

	i = 0;
	len_base = ft_strlen_pf(base);
	if (n < len_base)
		return (i + ft_dprintchar(fd, base[n]));
	else
	{
		i += ft_dprintnbr_base(fd, n / len_base, base);
		return (i + ft_dprintchar(fd, base[n % len_base]));
	}
}

int	ft_dprintptr(int fd, unsigned long long int n, char *base, int b)
{
	unsigned int	len_base;
	int				i;

	i = 0;
	if (!n)
		return (ft_dprintstr(fd, "(nil)"));
	if (b)
		i += ft_dprintstr(fd, "0x");
	len_base = ft_strlen_pf(base);
	if (n < len_base)
		return (i + ft_dprintchar(fd, base[n]));
	else
	{
		i += ft_dprintptr(fd, n / len_base, base, 0);
		return (i + ft_dprintchar(fd, base[n % len_base]));
	}
}
