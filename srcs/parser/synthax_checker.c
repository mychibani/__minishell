/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:56:19 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/20 15:18:11 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		__lexer_size(t_lexer *lexer)
{
	int	i;

	i = 0;
	if (!lexer)
		return (0);
	while (lexer)
	{
		lexer = lexer->next;
		i++;
	}
	return (i);
}

t_lexer	*synthax_error(t_lexer *lexer, t_program_data *data)
{
	if (lexer)
	{
		__putstr_fd("minishell ~ syntax error near unexpected token`", 2);
		__putstr_fd(lexer->token, 2);
		__putstr_fd("\'\n", 2);
	}
	data->rv = 2;
	data->synthax_error = SYNTAX_ERROR;
	return (lexer);
}

t_lexer *check_if_no_word(t_lexer *lexer, t_program_data *data)
{
	if (lexer && lexer->type == PIPE)
		return (lexer);
	while (lexer)
	{
		if (lexer->type == WORD)
			return (NULL);
		lexer = lexer->next;
	}
	data->rv = 2;
	data->synthax_error = SYNTAX_ERROR;
	return (lexer);
}

static int	check_lexing(t_lexer *lexing, t_program_data *data)
{
	if (lexing->type == PIPE
		|| lexing->type == REDIRECTION || lexing->type == HERE_DOC)
	{
		if (!lexing->next
			|| lexing->next->type == PIPE
			|| lexing->next->type == REDIRECTION
			|| lexing->next->type == NEW_LINE)
		{
			if (lexing->next
				&& (lexing->next->type == REDIRECTION
					|| lexing->next->type == HERE_DOC))
				return (1);
			data->rv = 2;
			data->synthax_error = SYNTAX_ERROR;
			return (0);
		}
	}
	return (1);
}

t_lexer	*to_not_treat_token(t_lexer *lexer, t_program_data *data)
{
	if (lexer)
		__putstr_fd("minishell ~ Valid token detected but not handled in minishell\n", 2);
	data->rv = 2;
	data->synthax_error = SYNTAX_ERROR;
	return (lexer);
}
t_lexer	*synthax_checker(t_lexer **lexer, t_program_data *data)
{
	t_lexer *travel;

	travel = *lexer;
	if (check_if_no_word(travel, data))
		return (synthax_error(check_if_no_word(travel, data), data));
	while (travel)
	{
		if (travel->type == INVALID)
			return (to_not_treat_token(travel, data));
		if (!check_lexing(travel, data))
			return (synthax_error(travel, data));
		travel = travel->next;
	}
	return (NULL);
}