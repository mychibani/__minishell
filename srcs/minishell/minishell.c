/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:46:01 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/18 17:13:00 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_es;

int	minishell(t_program_data *data, t_user_input *ui)
{
	char	**inputs;
	char	*line;
	int		i;

	while (INFINITE)
	{
		init_signals();
		line = readline("minishell ~ ");
		if (line == NULL)
			break ;
		add_history(line);
		signal(SIGINT, ctrld_signal);
		inputs = __split(line, '\n');
		if (!inputs)
			return (__putstr_fd("can't split inputs\n", 2), 2);
		data->all_inputs = inputs;
		i = -1;
		while (inputs[++i])
			treat_usr_inputs(inputs[i], data, init_user_input_struct(ui));
		__lstclear(&ui->token, free);
		__free_tab(inputs);
		free(line);
		g_es = 0;
	}
	return (_SUCCESS_);
}

int	main(int ac, char **av, char **env)
{
	t_program_data	data;
	t_user_input	ui;

	(void)av;
	(void)env;
	__memset(&data, 0, sizeof(data));
	__memset(&ui, 0, sizeof(ui));
	if (ac > 1)
		return (__putstr_fd("usage <./minishell>\n", 2), 2);
	minishell(&data, &ui);
	__exit(&data, &ui, g_es);
	return (_SUCCESS_);
}
