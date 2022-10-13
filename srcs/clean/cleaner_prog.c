/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:30:48 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/13 16:13:48 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**__free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	__clean_input(t_user_input *ui, char **inputs, char *line)
{
	(void)ui;
	if (inputs)
		__free_tab(inputs);
	free(line);
}

void	__clean_env(t_env **env)
{
	t_env	*tmp;
	t_env	*to_free;

	tmp = *env;
	while (tmp)
	{
		to_free = tmp;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		tmp = tmp->next;
		free(to_free);
	}
	free(env);
}