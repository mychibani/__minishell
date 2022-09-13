/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_operator_fct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:41:52 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/13 19:23:16 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator(char **token, char *str, int i)
{
	while (str[i] && str[i] != ' ' && __is_operator(str[i]))
	{
		if (!add_char_token(str[i], token))
			return (MALLOC_ERROR);
		if ((int)__strlen(*token) == 2)
			break ;
		i++;
	}
	return (i);
}

int	get_word(char **token, char *str, int i)
{
	t_state quote_status;
	// t_state slash;

	quote_status = UNQUOTED;
	// slash = 0;
	while (str[++i])
	{
		// if (str[i] == '\\' && str[i + 1] && !slash)
		// {
		// 	slash = BACKSLASH;
		// 	if (add_char_token(str[i], token) < 0)
		// 		return (MALLOC_ERROR);
		// 	continue;
		// }
		// quote_status = return_quoted_state(str[i], quote_status, slash);
		if (add_char_token(str[i], token) < 0)
			return (MALLOC_ERROR);
		// slash = 0;
	}
	return (adjust_i(str, i, quote_status));
}