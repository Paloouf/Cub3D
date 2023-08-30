/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:40:37 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/16 09:41:25 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *arg)
{
	int	len;

	if (arg == NULL)
		return (write(1, "(null)", 6));
	else
	{
		len = ft_strlen(arg);
		ft_putstr_fd(arg, 1);
	}
	return (len);
}

int	ft_checkconv(va_list arg, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
	{
		ft_putchar_fd(va_arg(arg, int), 1);
		len++;
	}
	if (format == 's')
		len += ft_printstr(va_arg(arg, char *));
	if (format == 'p')
		len += ft_put_ptrf(va_arg(arg, void *));
	if (format == 'd' || format == 'i')
		len += ft_put_nbrf(va_arg(arg, int));
	if (format == 'u')
		len += ft_put_unbrf(va_arg(arg, unsigned int));
	if (format == 'x')
		len += ft_putstr_hex(va_arg(arg, unsigned int), B16L);
	if (format == 'X')
		len += ft_putstr_hex(va_arg(arg, unsigned int), B16U);
	if (format == '%')
		len += ft_printpercent();
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	int		i;
	va_list	arg;

	va_start(arg, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_checkconv(arg, format[i + 1]);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			len++;
		}
		i++;
	}
	va_end(arg);
	return (len);
}
