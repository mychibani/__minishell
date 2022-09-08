/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:46:01 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/08 14:49:07 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_signal(int sig)
{
	(void)sig;
	close(0);
	g_exit_status = 0;
}

void	treat_signal(int sig)
{
	(void)sig;
	g_exit_status = 130;
}

void	__signal(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrld_signal(int sig)
{
	(void)sig;
	g_exit_status = 0;
}

void	init_signals(void)
{
		signal(SIGINT, __signal);
		signal(SIGQUIT, SIG_IGN);
}

void	get_user_input(char *user_input)
{
	printf("user_input == %s\n", user_input);
}

int main(int ac, char **av, char **env)
{
	char *line;
	(void)av;
	(void)env;
	if (ac > 1)
		return (ft_putstr_fd("usage <./minishell>\n", 2), 2);
	while (1)
	{
		init_signals();
		line = readline("minishell ~ ");
		add_history(line);
		if (line == NULL)
			break ;
		get_user_input(line);
		signal(SIGINT, ctrld_signal);
		g_exit_status = 0;
		free(line);
	}
	printf("exit\n");
	exit(g_exit_status);
	return (1);
}
