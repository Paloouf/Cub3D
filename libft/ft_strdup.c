/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:45:34 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/07 12:58:32 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = (char *)malloc((ft_strlen(s) + 1));
	if (dup == 0)
		return (NULL);
	dup[0] = '\0';
	ft_memcpy(dup, s, ft_strlen(s) +1);
	return (dup);
}
