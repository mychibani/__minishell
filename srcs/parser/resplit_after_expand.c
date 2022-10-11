/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resplit_after_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:26:01 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 14:10:43 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lst_lexer_new_word(char *content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->type = WORD;
	new->empty = 0;
	new->token = __strdup(content);
	if (!new->token)
		return (NULL);
	new->next = NULL;
	return (new);
}

int	insert_first_token(t_lexer *lexer, char *token)
{
	char	*tmp;

	tmp = __strdup(token);
	if (!tmp)
		return (0);
	free(lexer->token);
	lexer->token = tmp;
	return (1);
}

int	insert_token(char *token, t_lexer *lexer, int start, t_lexer *end)
{
	static int	state = 1;
	t_lexer		*new;

	if (start)
	{
		state = 1;
		return (1);
	}
	if (state)
	{
		state = 0;
		return (insert_first_token(lexer, token));
	}
	new = lst_lexer_new_word(token);
	if (!new)
		return (0);
	while (lexer->next != end)
		lexer = lexer->next;
	new->next = lexer->next;
	lexer->next = new;
	return (1);
}

int	split_token(t_lexer *lexer)
{
	t_lexer		*new_end;
	char		*to_split;
	char		**splitted_token;
	int			i;

	to_split = __strtrim(lexer->token, " \f\t\n\v");
	if (!to_split)
		return (0);
	splitted_token = unquoted_char_split(to_split, " \n");
	free(to_split);
	if (!splitted_token)
		return (0);
	new_end = lexer->next;
	i = 0;
	while (splitted_token[i])
	{
		if (!insert_token(splitted_token[i], lexer, 0, new_end))
			return (__free_tab(splitted_token), 0);
		i++;
	}
	__free_tab(splitted_token);
	insert_token(NULL, NULL, 1, NULL);
	return (1);
}

int	__split_token_after_expand(t_lexer *travel)
{
	int		prev_type;

	prev_type = -1;
	while (travel)
	{
		if (travel->type == WORD && prev_type != HERE_DOC
			&& prev_type != REDIRECTION && (travel->token[0] != '"'
				|| travel->token[__strlen(travel->token) - 1] != '"'
				|| __strlen(travel->token) > 1))
			if (!split_token(travel))
				return (MALLOC_ERROR);
		prev_type = travel->type;
		travel = travel->next;
	}
	return (1);
}
