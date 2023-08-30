/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:46:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/02/15 17:54:04 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;

	new = 0;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		ft_lstadd_back(&new, ft_lstnew(f(lst->content)));
		if (!new)
		{
			ft_lstdelone(new, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new);
}
