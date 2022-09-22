/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:18:34 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/22 13:40:50 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// int	__handle_here_doc(t_lexer *start, t_lexer *end, t_program_data *data)
// {
// 	pid_t		pid;
// 	char		*eof;
// 	t_lexer	*save;

// 	save = start;
// 	while (start != end && start && start->next != end)
// 	{
// 		if (start->type == HERE_DOC)
// 		{
// 			eof = start->next->token;
// 			pid = fork();
// 			if (!pid)
// 				init_child_hd(eof, start, save, data);
// 			else
// 			{
// 				if (wait_here_doc() == 130)
// 					return (130);
// 				if ()
// 			}
// 			/*
// 			** fork
// 			*/
// 		}
// 		start = start->next;
// 	}
// 	return (1);
// }

int	__heredoc(t_user_input *ui, t_program_data *data)
{
	// ui->ret_hd = __handle_here_doc(ui->lexer, ui->error_delim, data);
	// if (ui->ret_hd == 0)
	// 	return (__lex_clear(&ui->lexer), __exit(data, ui, 0), 0);
	// else if (ui->ret_hd == 130)
	// 	return (__lex_clear(&ui->lexer), 0);
	// else
		return (_SUCCESS_);
}