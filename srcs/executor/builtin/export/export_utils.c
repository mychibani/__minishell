/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:54:01 by caubry            #+#    #+#             */
/*   Updated: 2022/10/03 20:57:07 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **to_free, int i)
{
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

int	ft_var_length(char	*var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	// if (!var[i])
	// 	return (-1);
	return (i);
}

int	ft_valid_var(char *str)
{
	char	*name;
	int		length_name;
	int		i;

	i = 0;
	length_name = ft_var_length(str);
	name = malloc(sizeof(char) * length_name + 1);
	if (!name)
		return (-1);
	name = __strncpy(name, str, length_name);
	while (name[i])
	{
		if (__strchr("'@~-#{}!?/\\$.,", name[i]))
			return (free(name), 0);
		if (name[i] == '+' && name[i + 1])
			return (free(name), 0);
		i++;
	}
	free(name);
	return (1);
}

void	ft_concat_var(t_env *env, char *var_to_split)
{
	char	*tmp;
	char	*value;
	int		length_name;
	int		length_value;

	length_name = ft_var_length(var_to_split);
	length_value = __strlen(var_to_split) - length_name - 1;
	tmp = malloc(sizeof(char) * __strlen(var_to_split) - length_name);
	if (!tmp)
		return ;
	tmp = __strncpy(tmp, var_to_split + length_name + 1, length_value);
	value = _strjoin(env->value, tmp);
	free(tmp);
	env->value = value;
}
