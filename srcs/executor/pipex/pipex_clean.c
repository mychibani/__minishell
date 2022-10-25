/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:28:02 by caubry            #+#    #+#             */
/*   Updated: 2022/10/10 17:46:51 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_clean_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// void	_clean_exit(t_pipe *data)
// {
// 	clean(data);
// 	exit(0);
// }

void	free_content(t_cmd **lst)
{
	t_cmd	*move;
	t_cmd	*tmp;

	move = *lst;
	if (!move)
		return ;
	while (move)
	{
		tmp = move;
		if (move->cmd)
			_clean_char_tab(move->cmd);
		if (move->infile_name)
			_clean_char_tab(move->infile_name);
		if (move->outfile_name)
			_clean_char_tab(move->outfile_name);
		if (move->infile_type)
			_clean_char_tab(move->infile_type);
		if (move->outfile_type)
			_clean_char_tab(move->outfile_type);
		move = move->next;
		free(tmp);
	}
}

void	useless_fct(void *elem)
{
	(void)elem;
}

void	clean(t_pipe *data)
{
	t_cmd	*temp;

	temp = data->head;
	// if (data->limiter)
	// 	unlink("/tmp/heredoc.tmp");
	if (data->path)
		_clean_char_tab(data->path);
	free_content(&temp);
	// ft_lstclear(&temp, useless_fct);
	free(data->pid);
	free(data);
}
