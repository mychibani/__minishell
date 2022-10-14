/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:43:21 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/14 18:45:37 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(char *arg, char **to_tokenize, t_program_data *data)
{
	(void)data;
	if (!__strcmp(arg, ""))
		return (0);
	*to_tokenize = __strtrim(arg, " \f\t\r\v");
	if (!*to_tokenize)
		return (-1);
	if (!__strcmp(*to_tokenize, ""))
		return (free(*to_tokenize), 0);
	return (1);
}

int	treat_usr_inputs(char *arg, t_program_data *data, t_user_input *user_input)
{
	if (!check_input(arg, &user_input->to_tokenize, data))
		return (0);
	user_input->ret_token = tokenize(user_input->to_tokenize,
			&user_input->token);
	if (user_input->ret_token == MALLOC_ERROR)
		return (__putstr_fd("Malloc Error\n", 2), 2);
	if (user_input->ret_token == SYNTAX_ERROR)
		return (__putstr_fd("Syntax Error\n", 2), 2);
	free(user_input->to_tokenize);
	if (!lexer(user_input->token, &user_input->lexer))
		return (__putstr_fd("Lexer Error\n", 2), 2);
	user_input->error_delim = synthax_checker(&user_input->lexer, data);
	if (user_input->error_delim)
		return (__lexer_clear(&user_input->lexer), 0);
	if (!__heredoc(user_input, data))
		return (__lexer_clear(&user_input->lexer), 0);
	if (data->synthax_error == SYNTAX_ERROR)
		return (__lexer_clear(&user_input->lexer), -1);
	if (!sequence_launcher(user_input, data))
		return (__lexer_clear(&user_input->lexer), -1);
	return (_SUCCESS_);
}
