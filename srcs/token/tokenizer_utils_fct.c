/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_fct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:44:56 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/20 15:17:07 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__is_operator(char c)
{
	if (__strchr("|<>&", c))
		return (1);
	return (0);
}

t_state	return_quoted_state(char c, t_state quote, t_state slash)
{
	if (c == 39 && quote == S_QUOTED && !slash)
		return (UNQUOTED);
	else if (c == 34 && quote == D_QUOTED && !slash)
		return (UNQUOTED);
	else if (quote == UNQUOTED && !slash && (c == 39 || c == 34))
		quote = (c == 39) * S_QUOTED + (c == 34) * D_QUOTED;
	return (quote);
}

int	adjust_i(char *str, int i, int state)
{
	if (state != UNQUOTED)
		return (__putstr_fd("Unquoted sequence\n", 2), SYNTAX_ERROR);
	if (__is_operator(str[i]))
		--i;
	if (!str[i])
		i--;
	return (i);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}
