/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:49:03 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/02 19:10:02 by ychibani         ###   ########.fr       */
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