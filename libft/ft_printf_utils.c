/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:18:03 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/16 09:48:15 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_usize(unsigned int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_uitoa(unsigned int n)
{
	char			*str;
	size_t			i;
	unsigned int	nbr;

	nbr = n;
	i = 0;
	str = (char *)ft_calloc(sizeof(char), ft_usize(n) + 1);
	if (!str)
		return (NULL);
	while (i < ft_usize(n))
	{
		str[ft_usize(n) - i - 1] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	return (str);
}

int	ft_put_ptrf(void *ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += write(1, "(nil)", 5);
	else
	{
		len += write(1, "0x", 2);
		len += ft_putptr_hex((uintptr_t)ptr, B16L);
	}
	return (len);
}

int	ft_put_nbrf(int num)
{
	int		len;
	char	*str;

	str = ft_itoa(num);
	len = 0;
	len += ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

int	ft_put_unbrf(unsigned int num)
{
	int		len;
	char	*str;

	str = ft_uitoa(num);
	len = 0;
	len += ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
