/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_work.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:10:02 by caubry            #+#    #+#             */
/*   Updated: 2022/10/08 20:18:35 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_execute_command(t_program_data *data, t_user_input *ui)
{
	char	*new_command;

	new_command = find_command_path(data);
	if (!new_command)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(data->elem->cmd[0], STDERR_FILENO);
		ft_putstr_fd("\n", 2);
		if (data->index == data->ninst - 1)
		{
			free(new_command);
			// clean(data);
			exit(127);
		}
		free(new_command);
		// clean(data);
		exit(EXIT_FAILURE);
	}
	execve(new_command, data->elem->cmd, ui->env);
	free(new_command);
	perror(data->elem->cmd[0]);
	// clean(data);
	exit(EXIT_FAILURE);
}

void	infile_child_worker(t_program_data *data)
{
	char	**infile;
	int		i;

	infile = data->elem->infile_name;
	i = 0;
	// close(data->pipe[0]);
	while (infile && infile[i])
	{
		data->prev_read = open_infile(data->infile_name, data);
		i++;
	}
	_file_descriptors_duplicators(data->prev_read, data->pipe[1]);
	_close_file_descriptors(data->prev_read, data->pipe[1]);
	// _execute_command(data);
}

void	child_worker(t_program_data *data)
{
	_file_descriptors_duplicators(data->prev_read, data->pipe[1]);
	_close_file_descriptors(data->pipe[1], data->prev_read);
}

void	outfile_child_worker(t_program_data *data)
{
	char	**outfile;
	int		i;

	outfile = data->elem->outfile_name;
	i = 0;
	close(data->pipe[1]);
	while (outfile && outfile[i])
	{
		data->elem->outfile = open_outfile(data->elem->outfile, 0, data);
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
	// _execute_command(data);
}

void	exec_children_work(t_pipe *data, t_user_input *ui)
{
	close(data->pipe[0]);
	if (data->infile_name)
		infile_child_worker(data);
	if (data->outfile_name)
		outfile_child_worker(data);
	if (!data->infile && !data->outfile)
		child_worker(data);
	_execute_command(data, ui);
}
