/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:05:17 by ychibani          #+#    #+#             */
/*   Updated: 2021/11/27 19:25:53 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*__lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*begin_list;

	begin_list = 0;
	if (!lst || !f)
		return (0);
	while (lst)
	{
		node = __lstnew((*f)(lst->content));
		if (!node)
		{
			__lstclear(&begin_list, (*del));
			return (0);
		}
		__lstadd_back(&begin_list, node);
		lst = lst->next;
	}
	return (begin_list);
}
