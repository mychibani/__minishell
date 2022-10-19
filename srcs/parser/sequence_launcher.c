/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_launcher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:24:27 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/18 13:59:39 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_list_of_cmd(t_redirect *redir_list)
{
	while (redir_list)
	{
		printf("||%s||\n", redir_list->file_name);
		printf("[%d]\n", redir_list->type);
		redir_list = redir_list->next;
	}
}

void	print_command_list(t_cmd_list *cmd_list)
{
	while (cmd_list)
	{
		printf("%d\n", cmd_list->redirection[0]);
		printf("%d\n", cmd_list->redirection[1]);
		printf("%d\n", cmd_list->index);
		printf("%d\n", cmd_list->nb_cmd);
		print_redir_list_of_cmd(cmd_list->redirect);
		cmd_list = cmd_list->next;
	}
}

int	sequence_launcher(t_user_input *ui, t_program_data *data)
{
	t_lexer **seq;
	t_cmd_list	*cmd_list;

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
	__execute_sequence(cmd_list, data, ui);
	return (data->rv);
}
