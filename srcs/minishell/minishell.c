/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:46:01 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/13 19:46:05 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_es;

static char	**__free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static void	__exit(void)
{
	printf("exit\n");
	exit(g_es);
}

t_user_input *init_user_input_struct(t_user_input *ui)
{
	ui->token = NULL;
	ui->to_tokenize = NULL;
	ui->ret_hd = 0;
	ui->ret_token = 0;
	return (ui);
}

int	minishell(t_program_data *data, t_user_input *ui)
{
	char	**inputs;
	char	*line;
	int		i;

	while (1)
	{
		init_signals();
		line = readline("minishell ~ ");
		g_es = 0;
		add_history(line);
		if (line == NULL)
			break ;
		signal(SIGINT, ctrld_signal);
		inputs = __split(line, '\n');
		if (!inputs)
			return (__putstr_fd("can't split inputs", 2), 2);
		data->all_inputs = inputs;
		i = -1;
		while (inputs[++i])
			treat_usr_inputs(inputs[i], data, init_user_input_struct(ui));
		__free_tab(inputs);
		free(line);
	}
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_program_data	data;
	t_user_input	ui;
	(void)av;
	(void)env;

	if (ac > 1)
		return (__putstr_fd("usage <./minishell>\n", 2), 2);
	minishell(&data, &ui);
	return (__exit(), _SUCCESS_);
}
