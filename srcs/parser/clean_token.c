/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:59:04 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/04 15:23:45by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__error_after_expand(t_lexer **seq)
{
	t_lexer *save;
	t_lexer *prec;

	save = *seq;
	prec = NULL;
	while (save)
	{
		if (save->type == REDIRECTION && save->next && (save->next->token)[0] == '\0')
			return (__putstr_fd("minishell : ambiguous redirect\n", 2), -1);
		else if (save->type == WORD && prec && (save->token)[0] == '\0' && prec->type != HERE_DOC)
			save->empty = 1;
		else if (save->type == WORD && !prec && (save->token)[0] == '\0')
			save->empty = 1;
		prec = save;
		save = save->next;
	}
	return (1);
}

int	__error_catcher(t_lexer **seq, t_program_data *data)
{
	if (!*seq)
	{
		data->rv = 0;
		return (data->rv);
	}
	if (__error_after_expand(seq) == -1)
	{
		data->rv = 1;
		return (0);
	}
	return (1);
}