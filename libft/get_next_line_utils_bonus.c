/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:16:27 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/16 10:45:26 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcatgnl(char *dst, const char *src, size_t size)
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

char	*ft_strjoingnl(char *s1, const char *s2)
{
	char	*new;

	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	*new = 0;
	ft_strlcatgnl(new, s1, ft_strlen(s1) + 1);
	ft_strlcatgnl(new, s2, ft_strlen(s1) + (ft_strlen(s2) + 1));
	free(s1);
	return (new);
}

char	*ft_strchrgnl(char *str, char c)
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
