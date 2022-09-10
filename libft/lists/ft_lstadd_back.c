/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:33:15 by ychibani          #+#    #+#             */
/*   Updated: 2021/11/24 08:24:14 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__lstadd_back(t_list **alst, t_list *new)
{
	t_list	*elem;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	elem = __lstlast(*alst);
	elem->next = new;
}
