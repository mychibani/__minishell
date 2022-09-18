/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:52:55 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/18 19:38:49 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_type(char *to_cmp)
{
	if (!__strcmp(to_cmp, ">"))
		return (1);
	if (!__strcmp(to_cmp, "<"))
		return (1);
	if (!__strcmp(to_cmp, ">>"))
		return (1);
	if (!__strcmp(to_cmp, "<<"))
		return (2);
	return (0);
}

int	__get_type(char *to_cmp)
{
	if (!__strcmp(to_cmp, "|"))
		return (PIPE);
	if (!__strcmp(to_cmp, "\n"))
		return (NEW_LINE);
	if (redir_type(to_cmp) == 1)
		return (REDIRECTION);
	if (redir_type(to_cmp) == 2)
		return (HERE_DOC);
	if (!__is_operator(to_cmp[0]))
		return (WORD);
	return (INVALID);
}

t_lexer	*lst_lexer_new(void *content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->type = __get_type(content);
	new->empty = 0;
	new->hd_type = 0;
	new->token = __strdup(content);
	if (!new->token)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

void	lexer_add_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*travel;

	if (!*lexer)	
	{
		*lexer = new;
		return ;
	}
	travel = *lexer;
	while (travel->next)
		travel = travel->next;
	travel->next = new;
}

int	lexer(t_list *token, t_lexer **lexer)
{
	t_list	*temp;
	t_lexer	*to_add;

	temp = token;
	if (!temp)	
		return (0);
	while (temp)	
	{
		to_add = lst_lexer_new((char *)temp->content);
		if (!lexer)
			return (__lstclear(&token, free), 2);
		lexer_add_back(lexer, to_add);
		temp = temp->next;
	}
	return (_SUCCESS_);
}
