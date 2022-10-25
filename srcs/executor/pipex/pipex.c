/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:41 by caubry            #+#    #+#             */
/*   Updated: 2022/10/16 18:09:01 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__is_child(pid_t process)
{
	if (process == 0)
		return (1);
	else
		return (0);
}

int	pipex(t_pipe *data, t_user_input *ui)
{
	while (data->index < data->ninst)
	{
		if (pipe(data->pipe) < 0)
			return (perror("pipe"), 0);
		data->pid[data->index] = fork();
		if (data->pid[data->index] < 0)
			return (perror("fork "), 0);
		if (__is_child(data->pid[data->index]))
			exec_children_work(data, ui);
		if (!__is_child(data->pid[data->index]))
		{
			if (data->index)
				_close_file_descriptors(data->prev_read, data->pipe[1]);
			else
				close(data->pipe[1]);
			data->prev_read = data->pipe[0];
		}
		data->index++;
		data->elem = data->elem->next;
	}
	return (_SUCCESS_);
}

void	_wait(int *pid, t_pipe *data)
{
	int	i;
	int	wstatus;
	// (void) int	ret;

	// ret = 1;
	i = 0;
	while (i < (int)data->ninst)
		waitpid(pid[i++], &wstatus, 0);
	close(data->prev_read);
	// if (WIFEXITED(wstatus))
	// 	ret = WEXITSTATUS(wstatus);
	clean(data);
	// exit(ret);
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
	if (!pipex(ui->pipe, ui))
		return (STDERR_FILENO);
	// __printfcmd(ui->pipe->head);
	_wait(ui->pipe->pid, ui->pipe);
	// return (ft_cmd(ui));
	return(1);
}
