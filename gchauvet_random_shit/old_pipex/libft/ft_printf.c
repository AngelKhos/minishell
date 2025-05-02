/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:36:24 by ********          #+#    #+#             */
/*   Updated: 2025/01/27 13:10:37 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>

int	checkchar(size_t *i, const char *fmt, va_list	valist)
{
	int		len;
	size_t	tmp;

	len = 0;
	if (fmt[*i] == 's')
		len += ft_putstr((char *)va_arg(valist, const char *), 1);
	if (fmt[*i] == 'i' || fmt[(*i)] == 'd')
		len += ft_putnbr((int)va_arg(valist, int), 1);
	if (fmt[*i] == 'c')
		len += ft_putchar((unsigned char)va_arg(valist, int), 1);
	if (fmt[*i] == 'X')
		len += ft_puthex(va_arg(valist, unsigned int), "0123456789ABCDEF", 0);
	if (fmt[*i] == 'x')
		len += ft_puthex(va_arg(valist, unsigned int), "0123456789abcdef", 0);
	if (fmt[*i] == 'p')
	{
		tmp = (unsigned long)va_arg(valist, void *);
		if (tmp)
			len += ft_putstr("0x", 1);
		len += ft_puthex(tmp, "0123456789abcdef", 1);
	}
	if (fmt[(*i)] == 'u')
		len += ft_putunbr((int)va_arg(valist, int), 1);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	int		len;
	size_t	i;
	va_list	valist;

	i = 0;
	len = 0;
	if (!fmt)
		return (-1);
	va_start(valist, fmt);
	while (fmt[i])
	{
		if (fmt[i] != '%')
			len += write(1, fmt + i, 1);
		if (fmt[i] == '%')
		{
			i++;
			len += checkchar(&i, fmt, valist);
			if (fmt[i] == '%')
				len += ft_putchar('%', 1);
		}
		i++;
	}
	va_end(valist);
	return (len);
}
