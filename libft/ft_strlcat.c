/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:57:06 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/11 12:42:08 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t					i;
	size_t					j;

	i = 0;
	j = 0;
	if (!src || !size)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	while (src[j] != '\0' && (i + j) < size - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = 0;
	return (i + ft_strlen(src));
}
