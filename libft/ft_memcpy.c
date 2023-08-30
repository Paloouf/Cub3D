/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:38:39 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/16 11:07:10 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	char				*d;
	const char			*s;
	long unsigned int	i;

	i = 0;
	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (i < size)
	{
		d[i] = s[i];
		i ++;
	}
	return (dest);
}
