/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:03:22 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 14:04:15 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__lexer_size(t_lexer *lexer)
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
	__putstr_fd("minishell ~ syntax error near unexpected token`", 2);
	if (lexer)
		__putstr_fd(lexer->token, 2);
	__putstr_fd("\'\n", 2);
	data->rv = 2;
	data->synthax_error = SYNTAX_ERROR;
	return (lexer);
}
