/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:02:31 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/06 14:47:48 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	unsigned long	pos;
	int				delta;

	pos = 0;
	while (pos < size)
	{
		delta = *(unsigned char *)ptr1++ - *(unsigned char *)ptr2++;
		if (delta != 0)
			return (delta);
		pos++;
	}
	return (0);
}
