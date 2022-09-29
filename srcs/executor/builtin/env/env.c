/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:36:36 by caubry            #+#    #+#             */
/*   Updated: 2022/09/29 13:16:55 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__env_clear(t_env **lst, void (*del)(void*))
{
	t_env	*to_delete;

	if (!*lst)
		return ;
	while (*lst)
	{
		to_delete = *lst;
		(*del)(to_delete->name);
		(*del)(to_delete->value);
		*lst = to_delete->next;
		free(to_delete);
	}
	*lst = NULL;
}

char	**ft_env(t_user_input *ui)
{
	int		i;
	char	**env;

	i = 0;
	env = ui->env;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (env);
}
