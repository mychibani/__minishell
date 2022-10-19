/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:12:15 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/18 13:13:25 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_cmd(t_lexer *lexer)
{
	int	size;

	size = 0;
	while (lexer)
	{
		if (lexer->type == REDIRECTION || lexer->type == HERE_DOC)
		{
			lexer = lexer->next->next;
			continue;
		}
		if (lexer->empty == 0)
			size++;
		lexer = lexer->next;
	}
	return (size);
}

t_cmd_list *cmd_new(int	nb_cmd, t_program_data *data, int index, t_user_input *ui)
{
	t_cmd_list *cmd;

	cmd = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!cmd)
		return (0);
	cmd->redirection[0] = -1;
	cmd->redirection[1] = -1;
	cmd->data = data;
	cmd->index = index;
	cmd->redirect = NULL;
	cmd->nb_cmd = nb_cmd;
	cmd->arg = (char **)malloc(sizeof(char *) * nb_cmd);
	cmd->envp = ui->test_env;
	cmd->next = NULL;
	if (!cmd->arg)
		return (0);
	return (cmd);
}

t_redirect *create_new_redir(t_lexer *lexer)
{
	t_redirect *new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->file_name = lexer->next->token;
	new->next = NULL;
	if (!__strcmp(lexer->token, "<<"))
		new->type = HD;
	if (!__strcmp(lexer->token, ">"))
		new->type = GREAT;
	if (!__strcmp(lexer->token, "<"))
		new->type = LESS;
	if (!__strcmp(lexer->token, ">>"))
		new->type = D_GREAT;
	return (new);
}

void	redirect_add_back(t_redirect **start, t_redirect *new)
{
	t_redirect *tmp;

	tmp = *start;
	if (!*start)
	{
		*start = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	add_redirect(t_cmd_list *elem, t_lexer *lexer)
{
	t_redirect *new_redir;

	new_redir = create_new_redir(lexer);
	if (!new_redir)
		return (0);
	redirect_add_back(&(elem)->redirect, new_redir);
	return (1);
}

void	redirect_clear(t_redirect *to_clean)
{
	t_redirect	*next_to_free;

	if (!to_clean)
		return ;
	while (to_clean)
	{
		next_to_free = to_clean->next;
		free(to_clean);
		to_clean = NULL;
		to_clean = next_to_free;
	}
}

int	setup_arg_and_redirect(t_cmd_list *elem, t_lexer **lexer)
{
	int	i;

	i = 0;
	while (*lexer)	
	{
		if ((*lexer)->type == REDIRECTION || (*lexer)->type == HERE_DOC)
		{
			if (!add_redirect(elem, *lexer))
				return (redirect_clear(elem->redirect), 0);
			(*lexer) = (*lexer)->next->next;
			continue;
		}
		if (!(*lexer)->empty == 0)
			elem->arg[i++] = (*lexer)->token;
		(*lexer) = (*lexer)->next;
	}
	return (1);
}

void	cmd_add_back(t_cmd_list **start, t_cmd_list *new)
{
	t_cmd_list *travel;

	if (!*start)
		*start = new;
	else
	{
		travel = *start;
		while (travel->next)
			travel = travel->next;
		travel->next = new;
	}
}

int	cmd_list_creator(t_cmd_list **cmd_list, t_lexer **lexer, t_program_data *data, int index)
{  
	t_cmd_list *new;

	new = cmd_new(get_nb_cmd(*lexer), data, index);
	if (!new)
		return (0);
	if (!setup_arg_and_redirect(new, lexer))
		return (0);
	cmd_add_back(cmd_list, new);
	return (1);
}

void	cmd_list_free(t_cmd_list **cmd_list_free)
{
	t_cmd_list *next_to_free;
	
	while ((*cmd_list_free))
	{
		next_to_free = (*cmd_list_free)->next;
		if ((*cmd_list_free)->redirect)
			redirect_clear((*cmd_list_free)->redirect);
		if ((*cmd_list_free)->arg)
			__free_tab((*cmd_list_free)->arg);
		free((*cmd_list_free);
		*cmd_list_free = next_to_free;
	}
}

t_cmd_list	*create_cmd_list(t_lexer *lexer, t_program_data *data)
{
	t_cmd_list	*cmd_list_start;
	t_lexer		**save;
	int			index;

	index = 0;
	save = &lexer;
	cmd_list_start = NULL;
	while (lexer)
	{
		if (!cmd_list_creator(&cmd_list_start, &lexer, data, index))
			return (cmd_list_free(cmd_list_start), NULL);
		if (lexer)
			lexer = lexer->next;
		index++;
	}
	__lexer_clear(save);
	return (cmd_list_start);
}