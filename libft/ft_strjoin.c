/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:40:39 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/11 12:35:32 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	*new = 0;
	ft_strlcat(new, s1, ft_strlen(s1) + 1);
	ft_strlcat(new, s2, ft_strlen(s1) + (ft_strlen(s2) + 1));
	return (new);
}
