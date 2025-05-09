/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:41:34 by authomas          #+#    #+#             */
/*   Updated: 2025/01/27 17:09:51 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr_base(unsigned int n, char *base)
{
	unsigned int	len_base;
	int				i;

	i = 0;
	len_base = ft_strlen_pf(base);
	if (n < len_base)
		return (i + ft_printchar(base[n]));
	else
	{
		i += ft_printnbr_base(n / len_base, base);
		return (i + ft_printchar(base[n % len_base]));
	}
}

int	ft_printptr(unsigned long long int n, char *base, int b)
{
	unsigned int	len_base;
	int				i;

	i = 0;
	if (!n)
		return (ft_printstr("(nil)"));
	if (b)
		i += ft_printstr("0x");
	len_base = ft_strlen_pf(base);
	if (n < len_base)
		return (i + ft_printchar(base[n]));
	else
	{
		i += ft_printptr(n / len_base, base, 0);
		return (i + ft_printchar(base[n % len_base]));
	}
}
