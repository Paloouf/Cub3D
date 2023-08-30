/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:21:25 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/07 12:08:53 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;
	size_t	buff;

	buff = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	else if (buff / size != nmemb || buff / nmemb != size)
		return (NULL);
	else
	{
		out = malloc(buff);
		if (!out)
			return (NULL);
		ft_bzero(out, buff);
	}
	return (out);
}
