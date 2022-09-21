/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:46:01 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/21 20:01:35 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_es;

void ft_readline(char *s, int proc)
{
	char	*line;
	int	i;

	i = 1;
	while (i)
	{
		line = readline("?> ");
		if (line == NULL)
			break ;
		// add_history(line);
		if (!__strncmp(line, s, __strlen(line)))
			i = 0;
		free(line);
	}
	if (proc > 0)
	{
		printf("processus fils termine !\n");
		exit(EXIT_SUCCESS);
	}
	else
		return;
}

int	ft_test(t_list *start)
{
	pid_t pid;
	
	// if (heredoc->next->next)
	// 	ft_test(heredoc->next, i++);
	pid = fork();
	if (pid == 0)
	{
		ft_readline((char *)start->content, 1);
	}
	else
	{
		wait(&pid);
		ft_readline((char *)start->next->content, 0);
	}
	return (1);
}

int	minishell(t_program_data *data, t_user_input *ui)
{
	char	**inputs;
	char	*line;
	int		i;
	t_list	*start;
	t_list	*tmp;
	(void)	*data;
	(void)	*ui;

	while (INFINITE)
	{
		init_signals();
		line = readline("minishell ~ ");
		if (line == NULL)
			break ;
		add_history(line);
		// inputs = __split(line, '\n');
		// if (!inputs)
		// 	return (__putstr_fd("can't split inputs\n", 2), 2);
		// data->all_inputs = inputs;
		// i = -1;
		// while (inputs[++i])
		// 	treat_usr_inputs(inputs[i], data, init_user_input_struct(ui));
		// __clean_input(ui, inputs, line);
		// printf("g_es = %d\n", g_es);
		// g_es = 0;

		// TEST POUR HEREDOCS
		
		inputs = __split(line, '<');
		start = malloc(sizeof(t_list *));
		start = NULL;
		i = 1;
		while (inputs[i])
		{
			__lstadd_back(&start, __lstnew(inputs[i]));
			i++;
		}
		tmp = start;
		ft_test(tmp);
		__lstclear(&start, free);
	}
	return (_SUCCESS_);
}

int	main(int ac, char **av, char **env)
{
	t_program_data	data;
	t_user_input	ui;

	(void)av;
	(void)env;
	__init_structs(&data, &ui, env);
	if (ac > 1)
		return (__putstr_fd("usage <./minishell>\n", 2), 2);
	minishell(&data, &ui);
	__exit(&data, &ui, g_es);
	return (_SUCCESS_);
}

