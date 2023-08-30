/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:45:28 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/07 12:12:15 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int src, size_t n)
{
	long unsigned int	i;
	char				*d;

	d = dest;
	i = 0;
	while (i < n)
	{
		d[i] = src;
		i++;
	}
	return (dest);
}
