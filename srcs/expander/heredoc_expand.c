/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:46:39 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/03 14:15:58 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__heredoc_expansion(char **token, t_program_data *data)
{
	char	*str;
	int		i;
	char	*expanded_wd;

	i = -1;
	str = *token;
	expanded_wd = __strdup("");
	while (str[++i])
	{
		if (str[i] == '$' && (is_valid_char(str[i + 1]) || str[i + 1] == '?'))
		{
			if (parameter_expand(str + i + 1, &expanded_wd, data, &i) == MALLOC_ERROR)
				return (free(expanded_wd), MALLOC_ERROR);
		}
		else if (add_char_token(str[i], &expanded_wd) == MALLOC_ERROR)
			return (free(expanded_wd), MALLOC_ERROR);
	}
	update_token(token, &expanded_wd);
	return (_SUCCESS_);
}

	