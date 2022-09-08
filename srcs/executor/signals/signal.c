/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:04:32 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/08 15:21:37 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_es;

void	hd_signal(int sig)
{
	(void)sig;
	close(0);
	g_es = 0;
}

void	treat_signal(int sig)
{
	(void)sig;
	g_es = 130;
}

void	__signal(int sig)
{
	if (sig == SIGINT)
	{
		g_es = 130;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrld_signal(int sig)
{
	(void)sig;
	g_es = 0;
}

void	init_signals(void)
{
		signal(SIGINT, __signal);
		signal(SIGQUIT, SIG_IGN);
}