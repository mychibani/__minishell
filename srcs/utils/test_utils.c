/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:17:04 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 15:16:46 by ychibani         ###   ########.fr       */
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
		__printf("[%s]\n", lexer->token);
		__printf("[%d]\n", lexer->type);
		__printf("[%d]\n", lexer->hd_type);
		__printf("-                                -\n");
		lexer = lexer->next;
	}
	__printf("-----------------------\n");
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
