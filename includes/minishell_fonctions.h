/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fonctions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:42:53 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/10 18:02:10 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FONCTIONS_H
# define MINISHELL_FONCTIONS_H

/*
**		Cd
*/

int	change_directory(char *path);

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