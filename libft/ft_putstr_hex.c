/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:48:39 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/16 09:42:04 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	int	p;

	p = write(1, &c, 1);
	if (p < 0)
		return (-1);
	return (p);
}

int	ft_putstr_hex(unsigned int num, char *base)
{
	int	len;

	len = 0;
	if (num >= 16)
		len += ft_putstr_hex(num / 16, base);
	ft_putchar(base[num % 16]);
	len++;
	return (len);
}

int	ft_putptr_hex(uintptr_t num, char *base)
{
	int	len;

	len = 0;
	if (num >= 16)
		len += ft_putptr_hex(num / 16, base);
	ft_putchar(base[num % 16]);
	len++;
	return (len);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}
