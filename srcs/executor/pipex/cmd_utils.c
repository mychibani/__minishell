/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:26:52 by caubry            #+#    #+#             */
/*   Updated: 2022/10/10 17:38:20 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__count_cmd(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	__fill_infile_outfile(t_lexer **lexer, char **name, char **type)
{
	t_lexer	*tmp;

	tmp = *lexer;
	*name = __strjoin(*name, tmp->next->token);
	*name = __strjoin(*name, "\n");
	*type = __strjoin(*type, tmp->token);
	*type = __strjoin(*type, "\n");
	*lexer = tmp->next->next;
}

t_cmd	*ft_cmd_new(t_lexer *lexer, t_cmd *new)
{
	char	*outfiles;
	char	*infiles;
	char	*outfile_type;
	char	*infile_type;
	char	*cmd;

	outfiles = NULL;
	infiles = NULL;
	outfile_type = NULL;
	infile_type = NULL;
	cmd = NULL;
	while (lexer && lexer->type != PIPE)
	{
		if (!__strcmp(lexer->token, ">")
			|| !__strcmp(lexer->token, ">>"))
			__fill_infile_outfile(&lexer, &outfiles, &outfile_type);
		else if (!__strcmp(lexer->token, "<")
			|| !__strcmp(lexer->token, "<<"))
			__fill_infile_outfile(&lexer, &infiles, &infile_type);
		else
		{
			if (cmd)
				cmd = __strjoin(cmd, "\n");
			cmd = __strjoin(cmd, lexer->token);
			lexer = lexer->next;
		}
	}
	new->cmd = __split(cmd, '\n');
	new->infile_name = __split(infiles, '\n');
	new->outfile_name = __split(outfiles, '\n');
	new->infile_type = __split(infile_type, '\n');
	new->outfile_type = __split(outfile_type, '\n');
	new->next = NULL;
	return (new);
}

t_cmd	*ft_split_cmd(t_lexer **lexer, t_cmd *head)
{
	t_cmd	*new;
	t_cmd	*tmp;
	t_lexer	*tmp_lexer;

	new = malloc(sizeof(t_cmd));
	tmp_lexer = *lexer;
	if (!(new))
		return (NULL);
	new = init_new_cmd(new);
	new = ft_cmd_new(tmp_lexer, new);
	if (!head)
		head = new;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	while (tmp_lexer && tmp_lexer->type != PIPE)
		tmp_lexer = tmp_lexer->next;
	if (tmp_lexer && tmp_lexer->type == PIPE)
		*lexer = tmp_lexer->next;
	else
		*lexer = tmp_lexer;
	return (head);
}
