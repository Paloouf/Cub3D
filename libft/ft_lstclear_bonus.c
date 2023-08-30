/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:55:07 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/15 16:32:14 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;

	elem = *lst;
	if (!del || !lst)
		return ;
	while (*lst)
	{
		elem = elem->next;
		del((*lst)->content);
		free(*lst);
		*lst = elem;
	}
	*lst = NULL;
}
