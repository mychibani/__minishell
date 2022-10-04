/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:46:01 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/04 13:48:28 by ychibani         ###   ########.fr       */
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
		__clean_input(ui, inputs, line);
		g_es = 0;
	}
	return (_SUCCESS_);
}

int	main(int ac, char **av, char **env)
{
	t_program_data	data;
	t_user_input	ui;

	(void)av;
	__init_structs(&data, &ui);
	if (ac > 1)
		return (__putstr_fd("usage <./minishell>\n", 2), 2);
	if (!get_env_var(&data, env, get_env_size(env)))
		return (-1);
	minishell(&data, &ui);
	printf("exit\n");
	__exit(&data, &ui, g_es);
	return (_SUCCESS_);
}
