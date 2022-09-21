/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:18:34 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/21 20:11:35 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	__handle_here_doc(t_lexer *start, t_lexer *end, t_program_data *data)
// {
// 	pid_t		pid;
// 	char		*eof;
// 	t_lexing	*save;

// 	save = start;
// 	while (start != end && start && start->next != end)
// 	{
// 		if (start->type == HERE_DOC)
// 		{
// 			/*
// 			** fork
// 			*/
// 		}
// 		start = start->next;
// 	}
// 	return (1);
// }

// int	__heredoc(t_user_input *ui, t_program_data *data)
// {
// 	ui->ret_hd = __handle_here_doc(ui->lexing, ui->error_delim, data);
// 	if (ui->ret_hd == 0)
// 		return (__lex_clear(&ui->lexing), __exit(data));
// 	else if (ui->ret_hd == 130)
// 		return (__lex_clear(&ui->lexing), 0);
// 	else
// 		return (_SUCCESS_);
// }