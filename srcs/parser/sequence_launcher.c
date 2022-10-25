/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_launcher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:24:27 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/25 19:40:11 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sequence_launcher(t_user_input *ui, t_program_data *data)
{
	t_lexer **seq;
	t_cmd	*cmd_list;

	seq = &ui->lexer;
	data->ui = ui;
	if (__expand_var(*seq, data) == MALLOC_ERROR)
		return (0);
	if (!__error_catcher(seq, data))
		return (data->rv);
	if (!__split_token_after_expand(*seq))
		return (0);
	if (!lexer_remove_quote(*seq))
		return (0);
	cmd_list = create_cmd_list(*seq, data);
	if (!cmd_list)
		return (0);
	data->rv = __execute_sequence(cmd_list, data);
	return (data->rv);
}
