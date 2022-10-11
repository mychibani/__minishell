/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:56:19 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 14:08:00 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*check_if_no_word(t_lexer *lexer, t_program_data *data)
{
	if (lexer && (lexer->type == OPERATOR || lexer->type == PIPE))
	{
		data->rv = 2;
		data->synthax_error = SYNTAX_ERROR;
		return (lexer);
	}
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
		if (!lexing->next || lexing->next->type == REDIRECTION
			|| lexing->next->type == NEW_LINE)
		{
			if (lexing->next
				&& (lexing->type == PIPE || lexing->next->type == REDIRECTION
					|| lexing->next->type == HERE_DOC))
				return (1);
			data->rv = 2;
			data->synthax_error = SYNTAX_ERROR;
			return (0);
		}
	}
	return (1);
}

void	to_not_treat_token(t_program_data *data)
{
	__putstr_fd(
		"minishell ~ Valid token detected but not handled in minishell\n", 2);
	data->rv = 2;
	data->synthax_error = SYNTAX_ERROR;
}

t_lexer	*synthax_checker(t_lexer **lexer, t_program_data *data)
{
	t_lexer	*travel;

	travel = *lexer;
	if (check_if_no_word(travel, data))
		return (synthax_error(check_if_no_word(travel, data), data));
	while (travel)
	{
		if (travel->type == INVALID)
			return (to_not_treat_token(data), travel);
		if (!check_lexing(travel, data))
			return (synthax_error(travel, data));
		travel = travel->next;
	}
	return (NULL);
}
