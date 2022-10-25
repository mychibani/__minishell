/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_work.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:10:02 by caubry            #+#    #+#             */
/*   Updated: 2022/10/10 16:08:45 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_execute_command(t_pipe *data, t_user_input *ui)
{
	char	*new_command;

	new_command = find_command_path(data);
	if (!ft_cmd_pipe(ui, data->elem->cmd))
	{
		if (!new_command)
		{
			__putstr_fd("command not found: ", STDERR_FILENO);
			__putstr_fd(data->elem->cmd[0], STDERR_FILENO);
			__putstr_fd("\n", 2);
			if (data->index == data->ninst - 1)
			{
				free(new_command);
				clean(data);
				__clean_env(ui->test_env);
				exit(127);
			}
			free(new_command);
			clean(data);
			__clean_env(ui->test_env);
			exit(EXIT_FAILURE);
		}
		// ft_cmd(ui);
		execve(new_command, data->elem->cmd, ui->env);
		free(new_command);
		perror(data->elem->cmd[0]);
	}
	clean(data);
	__clean_env(ui->test_env);
	exit(EXIT_FAILURE);
}

void	infile_child_worker(t_pipe *data)
{
	char	**infile;
	int		i;

	infile = data->elem->infile_name;
	i = 0;
	while (infile && infile[i])
	{
		
		data->prev_read = open_infile(data->elem->infile_name[i], data);
		i++;
	}
	dup2(data->prev_read, STDIN_FILENO);
	close(data->prev_read);
}

void	child_worker(t_pipe *data)
{
	_file_descriptors_duplicators(data->prev_read, data->pipe[1]);
	_close_file_descriptors(data->pipe[1], data->prev_read);
}

void	finish_worker(t_pipe *data)
{
	dup2(data->prev_read, STDIN_FILENO);
	_close_file_descriptors(data->pipe[1], data->prev_read);
}

void	outfile_child_worker(t_pipe *data)
{
	char	**outfile;
	int		i;

	outfile = data->elem->outfile_name;
	i = 0;
	close(data->pipe[1]);
	while (outfile && outfile[i])
	{
		data->elem->outfile = open_outfile(data->elem->outfile_name[i], data->elem->outfile_type[i], data);
		i++;
	}
	if (data->elem->infile_name)
	{
		dup2(data->elem->outfile, STDOUT_FILENO);
		close(data->elem->outfile);
	}
	else
	{
		_file_descriptors_duplicators(data->prev_read, data->elem->outfile);
		_close_file_descriptors(data->prev_read, data->elem->outfile);
	}
}

void	exec_children_work(t_pipe *data, t_user_input *ui)
{
	close(data->pipe[0]);
	if (data->elem->infile_name)
		infile_child_worker(data);
	if (data->elem->outfile_name)
		outfile_child_worker(data);
	if (!data->elem->infile_name && !data->elem->outfile_name)
	{
		if(data->index == (data->ninst - 1))
			finish_worker(data);
		else
			child_worker(data);
	}
	if (!data->elem->outfile_name && data->index == (data->ninst - 1))
	{
		dup2(data->prev_read, STDIN_FILENO);
		_close_file_descriptors(data->pipe[1], data->prev_read);
	}
	_execute_command(data, ui);
	
}
