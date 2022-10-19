/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:26:09 by caubry            #+#    #+#             */
/*   Updated: 2022/10/19 10:20:40 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_new_cmd(t_cmd *new)
{
	new->mode = 0;
	new->outfile = 0;
	new->cmd = NULL;
	new->infile_name = NULL;
	new->outfile_name = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*init_cmd_list(t_user_input *ui)
{
	t_cmd	*head;
	t_lexer	*split_cmd;

	split_cmd = ui->lexer;
	head = NULL;
	while (split_cmd)
		head = ft_split_cmd(&split_cmd, head);
	return (head);
}

void	init_pipe(t_user_input *ui, t_pipe *data)
{
	data->elem = init_cmd_list(ui);
	data->head = data->elem;
	data->ninst = __count_cmd(data->head);
	data->index = 0;
	data->pid = (int *)malloc(sizeof(int) * (data->ninst));
	data->path = get_path(ui->env);
	if (!data->pid)
		_error_prompt("error :");
}

void	init(t_pipe *data)
{
	data->prev_read = 0;
	data->head = NULL;
	data->elem = NULL;
	data->path = NULL;
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

int		init_seq(t_cmd_list *cmd, t_program_data *data, int fds[2], t_user_input *ui)
{
	cmd->envp = ui->env;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->index = 0;
	cmd->path = get_path(data->envp);
}