/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:08:42 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/02 19:41:32 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_testing_wd(char *start_wd, int *offset)
{
	int	i;
	char *testing_wd;

	i = 0;
	while (__isalnum(start_wd[i]) || start_wd[i] == '_')
		i++;
	testing_wd = __substr(start_wd, 0, i);
	if (!testing_wd)
		return (NULL);
	*offset += i;
	return (testing_wd);
}

int	find_key(char *testing_wd, char *env_str, t_program_data *data, int j)
{
	if (!strcmp(testing_wd, env_str) && data->envp[j][1][0] == '1' && __strchr(data->envp[j][0], '='))
		return (1);
	return (0);
}

char *handle_quotes_in_env(char *str)
{
	int		i;
	char	*tmp;

	tmp = __strdup("");
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (!add_char_token(str[i], &tmp))
				return (free(tmp), NULL);
		}
		if (!add_char_token(str[i], &tmp))
			return (free(tmp), NULL);
		i++;
	}
	return (tmp);
}

int	get_value(char *testing_wd, char *env_str, char **expanded_wd, char *key_value)
{
	char *final_str;

	free(testing_wd);
	free(env_str);
	final_str = handle_quotes_in_env(key_value);
	if (!final_str)
		return (MALLOC_ERROR);
	*expanded_wd = __strjoin(*expanded_wd, final_str);
	free(final_str);
	if (!*expanded_wd)
		return (MALLOC_ERROR);
	return (1);
}