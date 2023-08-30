/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:39:11 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/07 15:11:33 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (c == 0)
		return ((char *)str + ft_strlen(str));
	while (*str)
	{
		if (*str == (char) c)
			return ((char *) str);
		str++;
	}
	return (NULL);
}
