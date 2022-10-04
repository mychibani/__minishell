/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:36:36 by caubry            #+#    #+#             */
/*   Updated: 2022/10/03 21:12:31 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_init_env(char *var_to_split)
{
	char	*name;
	char	*value;
	t_env	*env;
	int		length_name;
	int		length_value;

	length_name = ft_var_length(var_to_split);
	length_value = __strlen(var_to_split) - length_name - 1;
	name = malloc(sizeof(char) * length_name + 1);
	if (!name)
		return (NULL);
	name = __strncpy(name, var_to_split, length_name);
	if ((size_t)length_name == __strlen(var_to_split))
	{
		env = __lst_env_new(name, NULL, 0);
		return (env);
	}
	value = malloc(sizeof(char) * length_value + 1);
	if (!value)
		return (NULL);
	value = __strncpy(value, var_to_split + length_name + 1, length_value);
	env = __lst_env_new(name, value, 1);
	return (env);
}

t_env	**ft_split_env(char	**env)
{
	t_env	**list_env;
	int		i;

	i = 0;
	list_env = malloc(sizeof(t_env) * (ft_size(env) + 1));
	if (!list_env)
		return (NULL);
	*list_env = NULL;
	while (env[i])
	{
		if (!*list_env)
			*list_env = ft_init_env(env[i]);
		else
			__env_lstadd_back(list_env, ft_init_env(env[i]));
		i++;
	}
	return (list_env);
}

void	ft_env(t_user_input *ui)
{
	t_env	*env;

	env = *(ui->test_env);
	while (env)
	{
		if (env->env == 1)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return ;
}
