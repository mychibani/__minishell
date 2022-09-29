/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:40:29 by caubry            #+#    #+#             */
/*   Updated: 2022/09/29 13:16:33 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

void	__env_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*elem;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	elem = *alst;
	while (elem->next)
	{
		elem = elem->next;
	}
	elem->next = new;
}

t_env	*__lst_env_new(char *name, char *value)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (!(var))
		return (NULL);
	var->name = name;
	var->value = value;
	var->next = NULL;
	return (var);
}

t_env	*ft_init_env(char *var_to_split)
{
	char	**var;
	t_env	*env;

	var = __split(var_to_split, '=');
	env = __lst_env_new(var[0], var[1]);
	return (env);
}

t_env	*ft_split_env(char	**env)
{
	t_env	**list_env;
	t_env	*tmp;
	int	i;

	i = 0;
	list_env = malloc(sizeof(t_env) * (ft_size(env) + 1));
	if (!list_env)
		return (NULL);
	*list_env = NULL;
	tmp = *list_env;
	while (env[i])
	{
		if (!tmp)
			tmp = ft_init_env(env[i]);
		else
			__env_lstadd_back(list_env, ft_init_env(env[i]));
		i++;
	}
	return (*list_env);
}
