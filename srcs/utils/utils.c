/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:44:08 by caubry            #+#    #+#             */
/*   Updated: 2022/09/27 09:44:40 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linked_list(t_list *list)
{
	while (list)
	{
		__printf("[%s] ", (char *)list->content);
		list = list->next;
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

void	print_token_list(t_token *token)
{
	while (token)
	{
		__printf("[%s] ", (char *)token->content);
		token = token->next;
	}
	__printf("\n");
}

void	print_data(t_program_data *data, t_user_input *ui)
{
	printf("[%s]\n", data->all_inputs[0]);
	print_lexer_list(ui->lexer);
}
