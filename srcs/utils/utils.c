/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:36:37 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/18 15:39:36by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__lexer_clear(t_lexer **lst, void (*del)(void*))
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

void	print_linked_list(t_list *list)
{
	while (list)
	{
		__printf("[%s] ", (char *)list->content);
		list = list->next;
	}
	__printf("\n");
}

void	print_token_list(t_token *token)
{
	while (token)
	{
		__printf("[%s] ", (char *)token->content);
		token = token->next;
	}
	__printf("\n");
}

void	print_lexer_list(t_lexer *lexer)
{
	while (lexer)
	{
		__printf("%s\n", (char *)lexer->token);
		if (lexer->type == PIPE)
			__printf("Pipe Type\n");
		if (lexer->type == NEW_LINE)
			__printf("New Line Type\n");
		if (lexer->type == WORD)
			__printf("Word Type\n");
		if (lexer->type == HERE_DOC)
			__printf("Here Doc Type\n");
		if (lexer->type == REDIRECTION)
			__printf("Redirection Type\n");
		if (lexer->type == INVALID)
			__printf("Unknown Type\n");
		lexer = lexer->next;
	}
	__printf("\n");
}

void	print_data(t_program_data *data, t_user_input *ui)
{
	printf("[%s]\n", data->all_inputs[0]);
	print_lexer_list(ui->lexer);
}