/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:15:50 by ********          #+#    #+#             */
/*   Updated: 2025/01/27 13:10:27 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <unistd.h>

int	ft_putnbr(int n, int fd)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		return (ft_putstr("-2147483648", fd));
	}
	if (n < 0)
	{
		len += write(fd, "-", 1);
		n = n * -1;
	}
	if (n >= 10)
	{
		len += ft_putnbr(n / 10, fd);
	}
	n = (n % 10 + '0');
	len += write(fd, &n, 1);
	return (len);
}

int	ft_putunbr(unsigned int n, int fd)
{
	int	len;

	len = 0;
	if (n >= 10)
	{
		len += ft_putunbr(n / 10, fd);
	}
	n = (n % 10 + '0');
	len += write(fd, &n, 1);
	return (len);
}

int	ft_puthex(size_t nbr, char *base, int isptr)
{
	int	len;

	len = 0;
	if (isptr && nbr == (unsigned long) NULL)
		return (write(1, "(nil)", 5));
	if (nbr >= 16)
	{
		len += ft_puthex(nbr / 16, base, 0);
		len += ft_putchar(base[nbr % 16], 1);
	}
	else
		len += ft_putchar(base[nbr], 1);
	return (len);
}
