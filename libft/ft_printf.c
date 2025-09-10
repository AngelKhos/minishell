/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:35:07 by authomas          #+#    #+#             */
/*   Updated: 2025/09/04 16:25:51 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_handle(int fd, const char param, va_list *ap)
{
	int	i;

	i = 0;
	if (param == 'c')
		i += ft_dprintchar(fd, va_arg(*ap, int));
	if (param == 's')
		i += ft_dprintstr(fd, va_arg(*ap, char *));
	if (param == 'd' || param == 'i')
		i += ft_dprintnbr(fd, va_arg(*ap, int));
	if (param == 'u')
		i += ft_dprintunbr(fd, va_arg(*ap, unsigned int));
	if (param == '%')
		i += ft_dprintchar(fd, '%');
	if (param == 'x')
		i += ft_dprintnbr_base(fd, va_arg(*ap, unsigned int),
				"0123456789abcdef");
	if (param == 'X')
		i += ft_dprintnbr_base(fd, va_arg(*ap, unsigned int),
				"0123456789ABCDEF");
	if (param == 'p')
	{
		i += ft_dprintptr(fd, va_arg(*ap,
					unsigned long long int), "0123456789abcdef", 1);
	}
	return (i);
}

static int	printf_core(int fd, const char *s, va_list *ap)
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i++] != '%')
			len += ft_dprintchar(fd, s[i - 1]);
		else
		{
			i++;
			if (ft_strchr_pf("csdiuxXp%", s[i - 1]))
				len += format_handle(fd, s[i - 1], ap);
			else if (!ft_isalpha(s[i - 1]))
				return (-1);
			else
			{
				len += ft_dprintchar(fd, '%');
				len += ft_dprintchar(fd, s[i - 1]);
			}
		}
	}
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	if (!s || write(1, 0, 0) == -1)
		return (-1);
	va_start(ap, s);
	len += printf_core(1, s, &ap);
	va_end(ap);
	return (len);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	if (!s || write(1, 0, 0) == -1)
		return (-1);
	va_start(ap, s);
	len += printf_core(fd, s, &ap);
	va_end(ap);
	return (len);
}
