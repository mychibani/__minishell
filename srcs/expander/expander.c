/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:15:31 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 17:20:31 by ychibani         ###   ########.fr       */
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

char	*get_key(char *str)
{
	return (__substr(str, 0, __strchr(str, '=') - str));
}

int	treat_final_rv(char **wd, int *offset, t_program_data *data)
{
	char	*tmp_wd;

	tmp_wd = __itoa(data->rv);
	if (!tmp_wd)
		return (MALLOC_ERROR);
	*wd = __strjoin(*wd, tmp_wd);
	if (!*wd)
		return (free(tmp_wd), MALLOC_ERROR);
	*offset += 1;
	return (1);
}

int	parameter_expand(char *str, char **expanded_wd,
						t_program_data *data, int *offset)
{
	int		j;
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
				return (get_value(testing_wd, env_str, expanded_wd,
						(__strchr(data->envp[j][0], '=') + 1)));
			free(env_str);
		}
		j++;
	}
	return (free(testing_wd), 1);
}
