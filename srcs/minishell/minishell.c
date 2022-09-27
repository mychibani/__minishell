/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:46:01 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/27 09:38:15 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_es;

void ft_readline(char *s, int proc, char **heredoc)
{
	char	*line;
	
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!__strncmp(line, s, __strlen(line)))
			break ;
		else
		{
			*heredoc = _strjoin(*heredoc, line);
			*heredoc = _strjoin(*heredoc, "\n");
		}
		free(line);
	}
	if (proc > 0)
	{
		printf("processus fils termine !\n");
		exit(EXIT_SUCCESS);
	}
	else
		return ;
}

int	ft_test(t_list *start, char **heredoc)
{
	pid_t pid;
	
	pid = fork();
	if (pid == 0)
	{
		ft_readline((char *)start->content, 1, heredoc);
	}
	else
	{
		wait(&pid);
		if (start->next->next)
			ft_test(start->next, heredoc);
		else
			ft_readline((char *)start->next->content, 0, heredoc);
	}
	return (1);
}

int	minishell(t_program_data *data, t_user_input *ui)
{
	char	**inputs;
	char	*line;
	int		i;
	(void)	*data;
	(void)	*ui;
	// char	*heredoc;
	// t_list	*start;
	// t_list	*tmp;


	while (INFINITE)
	{
		init_signals();
		line = readline("minishell ~ ");
		if (line == NULL)
			break ;
		add_history(line);
		inputs = __split(line, '\n');
		if (!inputs)
			return (__putstr_fd("can't split inputs\n", 2), 2);
		data->all_inputs = inputs;
		i = -1;
		while (inputs[++i])
			treat_usr_inputs(inputs[i], data, init_user_input_struct(ui));
		__clean_input(ui, inputs, line);
		// printf("g_es = %d\n", g_es);
		g_es = 0;

		// TEST POUR HEREDOCS
		
		// heredoc = NULL;
		// inputs = __split(line, '<');
		// start = malloc(sizeof(t_list *));
		// start = NULL;
		// i = 1;
		// while (inputs[i])
		// {
		// 	__lstadd_back(&start, __lstnew(inputs[i]));
		// 	i++;
		// }
		// tmp = start;
		// ft_test(tmp, &heredoc);
		// __lstclear(&start, free);
		// printf("%s", heredoc);
		// free(start);
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
