/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fonctions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:42:53 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/13 14:04:19 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FONCTIONS_H
# define MINISHELL_FONCTIONS_H

/*
**		Cd
*/

int	change_directory(char *path);

/*
**		Lexer
*/


t_state	return_quoted_state(char c, t_state state, t_state quoted);
int		tokenize(char *to_tokenize, t_list **token_list);
int		add_token(char *token, t_list **begin);
int		add_char_token(char c, char **token);
int		adjust_i(char *str, int i, int state);
int		get_operator(char **token, char *str, int i);
int		get_word(char **token, char *str, int i);
int		__is_operator(char c);
/*
**		Parsing
*/

void	treat_usr_inputs(char *user_input, t_program_data *data, t_user_input *ui);

/*
**		Signals
*/

void	treat_signal(int sig);
void	hd_signal(int sig);
void	init_signals(void);
void	ctrld_signal(int sig);
void	__signal(int sig);

#endif