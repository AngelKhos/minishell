/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:35:07 by authomas          #+#    #+#             */
/*   Updated: 2025/01/27 17:09:22 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sort(const char param, va_list *ap)
{
	int	i;

	i = 0;
	if (param == 'c')
		i += ft_printchar(va_arg(*ap, int));
	if (param == 's')
		i += ft_printstr(va_arg(*ap, char *));
	if (param == 'd' || param == 'i')
		i += ft_printnbr(va_arg(*ap, int));
	if (param == 'u')
		i += ft_printunbr(va_arg(*ap, unsigned int));
	if (param == '%')
		i += ft_printchar('%');
	if (param == 'x')
		i += ft_printnbr_base(va_arg(*ap, unsigned int), "0123456789abcdef");
	if (param == 'X')
		i += ft_printnbr_base(va_arg(*ap, unsigned int), "0123456789ABCDEF");
	if (param == 'p')
	{
		i += ft_printptr(va_arg(*ap,
					unsigned long long int), "0123456789abcdef", 1);
	}
	return (i);
}

static int	ft_act(const char *s, va_list *ap)
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i++] != '%')
			len += ft_printchar(s[i - 1]);
		else
		{
			i++;
			if (ft_strchr_pf("csdiuxXp%", s[i - 1]))
				len += ft_sort(s[i - 1], ap);
			else if (!ft_isalpha(s[i - 1]))
				return (-1);
			else
			{
				len += ft_printchar('%');
				len += ft_printchar(s[i - 1]);
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
	len += ft_act(s, &ap);
	va_end(ap);
	return (len);
}
