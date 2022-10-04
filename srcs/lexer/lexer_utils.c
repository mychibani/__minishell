/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:49:03 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/04 16:21:22 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__lexer_clear(t_lexer **lst)
{
	t_lexer	*next_to_free;

	if (!lst)
		return ;
	while (*lst && (*lst)->token)
	{
		next_to_free = (*lst)->next;
		free((*lst)->token);
		(*lst)->token = NULL;
		free(*lst);
		*lst = NULL;
		*lst = next_to_free;
	}
}

void	__lexer_clear2(t_lexer **lst, void (*del)(void*))
{
	t_lexer	*to_delete;

	if (!*lst)
		return ;
	while (*lst)
	{
		to_delete = *lst;
		(*del)(to_delete->token);
		*lst = to_delete->next;
		free(to_delete);
	}
	*lst = NULL;
}