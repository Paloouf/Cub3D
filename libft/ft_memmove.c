/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:25:16 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/11 12:39:38 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		i;

	i = 0;
	d = dest;
	s = src;
	if (d == s)
		return (d);
	if (d < s)
	{
		while (size--)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (size--)
			d[size] = s[size];
	}
	return (d);
}
