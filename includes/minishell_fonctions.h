/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fonctions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:42:53 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/08 15:24:23 by ychibani         ###   ########.fr       */
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

void	get_user_input(char *user_input);

/*
**		Signals
*/


void	treat_signal(int sig);
void	hd_signal(int sig);
void	init_signals(void);
void	ctrld_signal(int sig);
void	__signal(int sig);

#endif