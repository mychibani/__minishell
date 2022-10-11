/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_launcher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:24:27 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 17:24:18 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sequence_launcher(t_lexer **seq, t_program_data *data)
{
	if (__expand_var(*seq, data) == MALLOC_ERROR)
		return (0);
	if (!__error_catcher(seq, data))
		return (data->rv);
	if (!__split_token_after_expand(*seq))
		return (0);
	return (1);
}
