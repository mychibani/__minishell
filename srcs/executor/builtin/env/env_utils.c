/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:40:29 by caubry            #+#    #+#             */
/*   Updated: 2022/10/03 14:05:38 by caubry           ###   ########.fr       */
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

char	*__strncpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;

	i = 0;
	if (dstsize)
	{
		while (src[i] && i < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}

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
	value = malloc(sizeof(char) * length_value + 1);
	if (!name || !value)
		return (NULL);
	name = __strncpy(name, var_to_split, length_name);
	value = __strncpy(value, var_to_split + length_name + 1, length_value);
	env = __lst_env_new(name, value);
	return (env);
}

t_env	**ft_split_env(char	**env)
{
	t_env	**list_env;
	int	i;

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
