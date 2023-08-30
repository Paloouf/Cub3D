/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:36:37 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/11 12:38:35 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int c, size_t size)
{
	char	*mem;
	int		i;

	i = 0;
	mem = (char *) memoryBlock;
	while (size > 0)
	{
		if (mem[i] == (char) c)
			return ((void *)mem + i);
		i++;
		size--;
	}
	return (NULL);
}
