/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:46:01 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/08 15:23:20 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_es;

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
		g_es = 0;
		free(line);
	}
	printf("exit\n");
	exit(g_es);
	return (1);
}
