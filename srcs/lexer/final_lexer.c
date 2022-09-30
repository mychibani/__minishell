/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:15:31 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/30 15:21:59 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char(char c)
{
	if (__is_alnum(c))
		return (1);
	return (0);
}

int	is_in_double_quote(char *token)
{
	if (token[0] == '\"' && token[__strlen(token) - 1] == '\"')
		return (1);
	return (0);
}

char *get_key(char *str)
{
	return (__substr(str, 0, __strchr(str, '=') - str));	
}

int	paramaeter_expand(char *str, char *expanded_wd, t_program_data *data)
{
	int	j;
	char	*env_str;

	j = 0;
	while (data->envp[j])
	{
		if (data->envp[j][1][0] == '1' || data->envp[j][1][0] == '0')
		{
			env_str = get_key(data->envp[j][0]);
			if (!env_str)
				return (0);
		}
	}
}

int	__usual_expansion(char **token, t_program_data *data)
{
	char	*str;
	int		i;
	char	*expanded_wd;

	i = -1;
	str = *token;
	expanded_wd = __strdup("");
	while (str[++i])
	{
		if ((str[i] == '$') && is_valid_char(str[i + 1]))
		{
			if (parameter_expand(str + i + 1, &expanded_wd, data, &i))
				return (free(expanded_wd), 0);
		}
		if (!add_char_token(str[i], &expanded_wd))
			return (free(expanded_wd), 0);
	}
	return (_SUCCESS_);
}

int	__expand_var(t_lexer *seq, t_program_data *data)
{
	while (seq)
	{
		// if (seq->token == HERE_DOC)	
		// {
		// 	if (!__heredoc_expansion(&seq->next->token, data) && seq->next->hd_type == 1)
		// 		return (MALLOC_ERROR);
		// 	seq = seq->next->next;
		// }else 
		if (seq->token == WORD)
		{
			if (!__usual_expansion(&seq->token, data))
				return (MALLOC_ERROR);
			seq = seq->next;
		}
		else
			seq = seq->next;
	}
	return (_SUCCESS_);
}

int	sequence_launcher(t_lexer **seq, t_program_data *data)
{
	if (__expand_var(*seq, data) == MALLOC_ERROR)
		return (-1);
	print_lexer_list(*seq);
}