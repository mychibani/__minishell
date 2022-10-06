/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:15:31 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/06 11:31:05 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char(char c)
{
	if (__isalnum(c) || c == '_')
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

int	treat_final_rv(char **wd, int *offset, t_program_data *data)
{
	char *tmp_wd;

	tmp_wd = __itoa(data->rv);
	if (!tmp_wd)
		return (MALLOC_ERROR);
	*wd = __strjoin(*wd, tmp_wd);
	if (*wd)
		return (free(tmp_wd), MALLOC_ERROR);
	*offset += 1;
	return (1);
}

int	parameter_expand(char *str, char **expanded_wd, t_program_data *data, int *offset)
{
	int	j;
	char	*env_str;
	char	*testing_wd;

	if (str[0] == '?')
		return (treat_final_rv(expanded_wd, offset, data));
	testing_wd = get_testing_wd(str, offset);
	if (!testing_wd)
		return (MALLOC_ERROR);
	j = 0;
	while (data->envp[j])
	{
		if (data->envp[j][1][0] == '1' || data->envp[j][1][0] == '0')
		{
			env_str = get_key(data->envp[j][0]);
			if (!env_str)
				return (free(testing_wd), 0);
			if (find_key(testing_wd, env_str, data, j))
				return (get_value(testing_wd, env_str, expanded_wd, (__strchr(data->envp[j][0], '=') + 1)));
			free(env_str);
		}
		j++;
	}
	return (free(testing_wd), 1);
}

void	update_token(char **token, char **new_token)
{
	free(*token);
	*token = *new_token;
}

int	dollars_status(char *full_str, char *dollar)
{
	int	i;
	int	quote_status;

	i = 0;
	quote_status = 0;
	while (full_str[i] && &full_str[i] != dollar)
	{
		quote_status = return_quoted_state(full_str[i], quote_status, 0);
		i++;
	}
	if (quote_status == UNQUOTED || quote_status == D_QUOTED)
		return (0);
	return (1);
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
		if ((str[i] == '$') && is_valid_char(str[i + 1]) && !dollars_status(str, &str[i]))
		{
			if (parameter_expand(str + i + 1, &expanded_wd, data, &i) == MALLOC_ERROR)
				return (free(expanded_wd), MALLOC_ERROR);
		}
		else if (add_char_token(str[i], &expanded_wd) == MALLOC_ERROR)
			return (free(expanded_wd), MALLOC_ERROR);
	}
	update_token(token, &expanded_wd);
	return (_SUCCESS_);
}

int	__expand_var(t_lexer *seq, t_program_data *data)
{
	while (seq)
	{
		if (seq->type == HERE_DOC)	
		{
			if (!__heredoc_expansion(&seq->next->token, data) && seq->next->hd_type == 1)
				return (MALLOC_ERROR);
			seq = seq->next->next;
		}
		else if (seq->type == WORD)
		{
			if (__usual_expansion(&seq->token, data) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			seq = seq->next;
		}
		else
			seq = seq->next;
	}
	return (_SUCCESS_);
}

