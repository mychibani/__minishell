/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:15:31 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/29 15:36:17 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__usual_expansion(char **token, t_program_data *data)
{
	char	*str;
	int		i;
	char	*expanded_wd;

	i = -1;
	str = *token;
	while (str[++i])
	{
		if ((str[i] == '$') && is_valid_char(str[i + 1]))
	}
	return (_SUCCESS_);
}

int	__expand_var(t_lexer *seq, t_program_data *data)
{
	while (seq)
	{
		if (seq->token == HERE_DOC)	
		{
			if (!__heredoc_expansion(&seq->next->token, data) && seq->next->hd_type == 1)
				return (MALLOC_ERROR);
			seq = seq->next->next;
		}
		else if (seq->token == WORD)
		{
			if (!__usual_expansion(&seq->token, data))
				return (MALLOC_ERROR);
			seq = seq->next;
		}
		else
			seq = seq->next;
	}
	return (_SUCCESS_);
}

int	sequence_launcher(t_lexer **seq, t_program_data *data)
{
	if (__expand_var(*seq, data) == MALLOC_ERROR)
		return (-1);
}