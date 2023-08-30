/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:44:20 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/15 15:41:07 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buff;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			buff = ft_lstlast(*(lst));
			buff->next = new;
		}
	}
}
