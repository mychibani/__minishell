/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_operator_fct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:41:52 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/04 13:50:07 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_escape(int i, t_state state, char *str)
{
	if (state == S_QUOTED)
		return (0);
	if (state == D_QUOTED && __strchr("$`\\\"", str[i + 1]))
		return (1);
	if (state == UNQUOTED)
		return (1);
	return (0);
}

int	get_operator(char **token, char *str, int i)
{
	while (str[i] && str[i] != ' ' && __is_operator(str[i]))
	{
		if (*token && (int)__strlen(*token) == 1 && **token != str[i])
			return (i - 1);
		if (!add_char_token(str[i], token))
			return (MALLOC_ERROR);
		if ((int)__strlen(*token) == 2)
			break ;
		i++;
	}
	if (!__is_operator(str[i]))
		--i;
	if (!str[i])
		i--;
	return (i);
}

int	get_word(char **token, char *str, int i)
{
	t_state	quote_status;
	t_state	slash;

	quote_status = UNQUOTED;
	slash = 0;
	while (str[++i])
	{
		quote_status = return_quoted_state(str[i], quote_status, slash);
		if (quote_status == UNQUOTED && slash != BACKSLASH)
			if (__strchr("\f\t\n\r\v ", str[i]) || __is_operator(str[i]))
				break ;
		if (add_char_token(str[i], token) < 0)
			return (MALLOC_ERROR);
		slash = 0;
	}
	return (adjust_i(str, i, quote_status));
}
