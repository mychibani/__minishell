/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:41 by caubry            #+#    #+#             */
/*   Updated: 2022/10/07 19:03:23 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_new(t_lexer *lexer, t_cmd *new)
{
	while (lexer && lexer->type != PIPE)
	{
		if (lexer->type == REDIRECTION || lexer->type == HERE_DOC)
			lexer = ft_
	}
}

t_cmd	*init_new_cmd(t_cmd *new)
{
	new->mode = 0;
	new->outfile = 0;
	new->cmd = NULL;
	new->infile_name = NULL;
	new->outfile_name = NULL;
}

t_lexer	*ft_split_cmd(t_lexer *lexer, t_cmd *head)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = malloc(sizeof(t_cmd));
	if (!(new))
		return (NULL);
	new = init_new_cmd(new);
	new = ft_cmd_new(lexer, new);
	if (!head)
		head = new;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (lexer);
}

t_cmd	init_cmd_list(t_user_input *ui)
{
	t_cmd	*head;
	t_lexer	*split_cmd;

	split_cmd = ui->lexer;
	head = NULL;
	while (split_cmd)
	{
		split_cmd = ft_split_cmd(split_cmd, head);
	}
	return (head);
}

void	init_pipe(t_user_input *ui, t_pipe *data)
{
	data->elem = init_cmd_list(ui);
	data->head = data->elem;
	data->ninst = ft_lstsize(data->elem);
	data->index = 0;
	data->pid = (int *)malloc(sizeof(int) * (data->ninst));
	if (!data->pid)
		_error_prompt("error :");
}

void	init(t_pipe *data)
{
	data->prev_read = 0;
	data->head = NULL;
	data->elem = NULL;
	data->ninst = 0;
	data->index = 0;
	data = NULL;
}

t_pipe	*ft_init_pipex(t_user_input *ui, t_pipe *pipe)
{
	init(pipe);
	init_pipe(ui, pipe);
	return (pipe);
}

int	ft_pipex(t_user_input *ui)
{
	ui->pipe = malloc(sizeof(t_pipe));
	if (!ui->pipe)
		return (perror("error"), STDERR_FILENO);
	if (!ft_is_pipe(ui->lexer))
		return (ft_cmd(ui));
	if (!ft_init_pipex(ui, ui->pipe))
		return (STDERR_FILENO);
	return (ft_cmd(ui));
}