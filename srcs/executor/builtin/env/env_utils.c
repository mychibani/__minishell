/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:40:29 by caubry            #+#    #+#             */
/*   Updated: 2022/10/04 15:37:35 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

t_env	*__lst_env_new(char *name, char *value, int appear)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (!(var))
		return (NULL);
	var->name = name;
	var->value = value;
	var->env = appear;
	var->next = NULL;
	return (var);
}

char	*__strncpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;

	i = 0;
	if (!dstsize)
		dst[i] = '\0';
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

void	__env_clear(t_env **lst, void (*del)(void*))
{
	t_env	*to_delete;

	if (!*lst)
		return ;
	while (*lst)
	{
		to_delete = *lst;
		(*del)(to_delete->name);
		if (to_delete->value)
			(*del)(to_delete->value);
		*lst = to_delete->next;
		free(to_delete);
	}
}
