/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:55:04 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/11 12:37:11 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*str2;

	str2 = NULL;
	if (c == 0)
		return ((char *)str + ft_strlen(str));
	while (*str)
	{
		if (*str == (char) c)
			str2 = (char *) str;
		str++;
	}
	return (str2);
}
