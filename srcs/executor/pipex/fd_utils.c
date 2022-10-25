/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:27:24 by caubry            #+#    #+#             */
/*   Updated: 2022/10/10 16:27:46 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_close_file_descriptors(int _first, int _second)
{
	if (_first > 0)
		close(_first);
	if (_second > 0)
		close(_second);
	return (_SUCCESS_);
}

int	_file_descriptors_duplicators(int _first, int _second)
{
	if (_first > 0)
		dup2(_first, STDIN_FILENO);
	if (_second > 0)
		dup2(_second, STDOUT_FILENO);
	return (1);
}

int	open_infile(char *infile_name, t_pipe *data)
{
	int	infile;

	infile = open(infile_name, O_RDONLY);
	if (access(infile_name, R_OK))
	{
		__putstr_fd("pipex: ", STDERR_FILENO);
		__putstr_fd("no such file or directory: ", STDERR_FILENO);
		__putstr_fd(infile_name, STDERR_FILENO);
		__putstr_fd("\n", 2);
		_close_file_descriptors(data->pipe[0], data->pipe[1]);
		clean(data);
		exit(EXIT_FAILURE);
	}
	else if (infile < 0)
	{
		_close_file_descriptors(data->pipe[0], data->pipe[1]);
		clean(data);
		_error_prompt(infile_name);
	}
	else
		return (infile);
	return (infile);
}

int	open_outfile(char *outfile_name, char *mode, t_pipe *data)
{
	int	outfile;

	if (!__strcmp(mode, ">"))
		outfile = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		outfile = open(outfile_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
	{
		close(data->prev_read);
		_close_file_descriptors(data->pipe[0], data->pipe[1]);
		clean(data);
		_error_prompt(outfile_name);
	}
	return (outfile);
}
