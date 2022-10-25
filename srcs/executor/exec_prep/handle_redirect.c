/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:54:17 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/25 19:52:23 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	less_redirection(t_cmd *cmd_list)
{
	if (cmd_list->redirection[0] != -1)
		close(cmd_list->redirection[0]);
	if (!test_access(cmd_list))	
		return (0);
	cmd_list->redirection[0] = open(cmd_list->redirect->file_name, O_RDONLY);
	if (cmd_list->redirection[0] < 0)
		return (perror(cmd_list->redirect->file_name, "no such file or directory", NULL), 0);
	if (dup2(cmd_list->redirection[0], STDIN_FILENO) < 0)
		return (perror(cmd_list->redirect->file_name, "can't dup file :", NULL), 0);
	if (close(cmd_list->redirection[0]))
		return (perror(cmd_list->redirect->file_name, "can't close file :", NULL), 0);
	return (1);
}

int	great_redirection(t_cmd *cmd_list)
{
	if (cmd_list->redirection[1] != -1)
		close(cmd_list->redirection[1]);
	if (!test_access(cmd_list))	
		return (0);
	cmd_list->redirection[1] = open(cmd_list->redirect->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (cmd_list->redirection[1] < 0)
		return (perror(cmd_list->redirect->file_name, "no such file or directory", NULL), 0);
	if (dup2(cmd_list->redirection[1], STDOUT_FILENO) < 0)
		return (perror(cmd_list->redirect->file_name, "can't dup file :", NULL), 0);
	if (close(cmd_list->redirection[1]))
		return (perror(cmd_list->redirect->file_name, "can't close file :", NULL), 0);
	return (1);
}

int	dgreat_redirection(t_cmd *cmd_list)
{
	if (cmd_list->redirection[1] != -1)
		close(cmd_list->redirection[1]);
	if (!test_access(cmd_list))	
		return (0);
	cmd_list->redirection[1] = open(cmd_list->redirect->file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (cmd_list->redirection[1] < 0)
		return (perror(cmd_list->redirect->file_name), 0);
	if (dup2(cmd_list->redirection[1], STDOUT_FILENO) < 0)
		return (perror(cmd_list->redirect->file_name), 0);
	if (close(cmd_list->redirection[1]))
		return (perror(cmd_list->redirect->file_name), 0);
	return (1);
}

char	*__get_name(int name)
{
	char	*i;
	char	*hd_file;

	i = __itoa(name);
	if (!i)
		return (NULL);
	hd_file = __strjoin(__strdup(".hd_file"), i);
	if (!hd_file)
		return (free(i), NULL);
	return (free(i), hd_file);
}

int	hd_redirection(t_cmd *cmd_list)
{
	int		fd;
	char	*tmp_file;

	tmp_file = __get_name(cmd_list->index + 1);
	if (!tmp_file)
		return (0);
	fd = open(tmp_file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(tmp_file), 0);
	if (close(fd) < 0)
		return (perror(tmp_file), free(tmp_file), 0);
	if (cmd_list->redirection[0] != -1)
		close(cmd_list->redirection[0]);
	if (!test_access(cmd_list))	
		return (0);
	cmd_list->redirection[0] = open(tmp_file, O_RDONLY);
	if (cmd_list->redirection[0] < 0)
		return (perror(cmd_list->redirect->file_name), 0);
	if (dup2(cmd_list->redirection[0], STDIN_FILENO) < 0)
		return (perror(cmd_list->redirect->file_name), 0);
	if (close(cmd_list->redirection[0]))
		return (perror(cmd_list->redirect->file_name), 0);
	return (1);
}