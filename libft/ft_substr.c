/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:49:21 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/11 12:40:29 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		new = malloc((ft_strlen(s) + 1) - start);
	else
		new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[start] && len-- > 0)
		new[i++] = s[start++];
	new[i] = 0;
	return (new);
}
