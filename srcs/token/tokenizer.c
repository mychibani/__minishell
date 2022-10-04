/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:21:32 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/04 13:49:53 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_char_token(char c, char **token)
{
	char	*appened_token;
	int		i;
	int		token_len;

	i = 0;
	token_len = __strlen(*token);
	appened_token = (char *)malloc(sizeof(char) * (token_len + 2));
	if (!appened_token)
	{
		free(*token);
		*token = NULL;
		return (MALLOC_ERROR);
	}
	while (i < token_len)
	{
		appened_token[i] = (*token)[i];
		i++;
	}
	appened_token[token_len] = c;
	appened_token[token_len + 1] = '\0';
	free(*token);
	*token = appened_token;
	return (1);
}

int	add_token(char *token, t_list **begin)
{
	t_list	*adding_token;

	if (!token)
		return (MALLOC_ERROR);
	adding_token = __lstnew(token);
	if (!adding_token)
		return (MALLOC_ERROR);
	__lstadd_back(begin, adding_token);
	return (0);
}

int	init_token_if_none(char **token, int *status)
{
	if (!*status)
	{
		*token = __strdup("");
		if (!*token)
			return (MALLOC_ERROR);
		*status = 1;
	}
	return (1);
}

int	tokenize(char *to_tokenize, t_list **token_list)
{
	char	*new_token;
	int		i;	
	int		status;

	i = -1;
	status = 0;
	while (to_tokenize[++i])
	{
		skip_spaces(to_tokenize, &i);
		if (!init_token_if_none(&new_token, &status))
			return (free(new_token), __lstclear(token_list, free), i);
		if (__is_operator(to_tokenize[i]))
			i = get_operator(&new_token, to_tokenize, i);
		else
			i = get_word(&new_token, to_tokenize, i - 1);
		if (i < 0)
			return (free(new_token), __lstclear(token_list, free), i);
		if (add_token(new_token, token_list) < 0)
			return (free(new_token), __lstclear(token_list, free), -2);
		status = 0;
	}
	return (1);
}

/*
** 34 = Simple Quote
** 39 = Doubles Quote
*/