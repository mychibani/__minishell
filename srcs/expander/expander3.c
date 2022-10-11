/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:54:48 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 17:23:10 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_token(char **token, char **new_token)
{
	free(*token);
	*token = *new_token;
}

int	dollars_status(char *full_str, char *dollar)
{
	int	i;
	int	quote_status;

	i = 0;
	quote_status = 0;
	while (full_str[i] && &full_str[i] != dollar)
	{
		quote_status = return_quoted_state(full_str[i], quote_status, 0);
		i++;
	}
	if (quote_status == UNQUOTED || quote_status == D_QUOTED)
		return (0);
	return (1);
}

int	is_an_exception(char *tmp, int i)
{
	if (tmp[i + 1] && __strchr("?'", tmp[i + 1]))
		return (1);
	if (tmp[i + 1] && tmp[i + 1] == '"')
	{
		if (in_quote(&tmp[i], tmp) && tmp[i + 1] == '"')
			return (0);
		else
			return (1);
	}
	return (0);
}

int	__usual_expansion(char **token, t_program_data *data)
{
	char	*str;
	int		i;
	char	*expanded_wd;

	i = -1;
	str = *token;
	expanded_wd = __strdup("");
	while (str[++i])
	{
		if ((str[i] == '$' && is_valid_char(str[i + 1])
				&& !dollars_status(str, &str[i])) || is_an_exception(str, i))
		{
			if (parameter_expand(str + i + 1,
					&expanded_wd, data, &i) == MALLOC_ERROR)
				return (free(expanded_wd), MALLOC_ERROR);
		}
		else if (add_char_token(str[i], &expanded_wd) == MALLOC_ERROR)
			return (free(expanded_wd), MALLOC_ERROR);
	}
	update_token(token, &expanded_wd);
	return (_SUCCESS_);
}

int	__expand_var(t_lexer *seq, t_program_data *data)
{
	while (seq)
	{
		if (seq->type == HERE_DOC)
		{
			if (!__heredoc_expansion(&seq->next->token, data)
				&& seq->next->hd_type == 1)
				return (MALLOC_ERROR);
			seq = seq->next->next;
		}
		else if (seq->type == WORD)
		{
			if (__usual_expansion(&seq->token, data) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			seq = seq->next;
		}
		else
			seq = seq->next;
	}
	return (_SUCCESS_);
}
