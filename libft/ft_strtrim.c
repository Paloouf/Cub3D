/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:49:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/11 12:41:43 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_skip(char s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1 == s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_skip(s1[i], (char *)set) == 1)
		i++;
	while (ft_skip(s1[ft_strlen(s1) - j - 1], (char *)set) == 1)
		j++;
	return (ft_substr(s1, i, ft_strlen(s1) - i - j));
}
