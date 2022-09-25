/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:49:03 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/25 20:00:23 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__lexer_clear(t_lexer **lst, void (*del)(void*))
{
	t_lexer	*to_delete;

	if (!*lst)
		return ;
	(void)del;
	while (*lst)
	{
		to_delete = *lst;
		free((*lst)->token);
		*lst = to_delete->next;
		free(to_delete);
	}
	*lst = NULL;
}