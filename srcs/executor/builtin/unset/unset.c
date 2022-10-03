/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:35:26 by caubry            #+#    #+#             */
/*   Updated: 2022/10/03 14:29:09 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unsetvar(t_user_input *ui, char *var_to_unset)
{
	t_env	*previous;
	t_env	*unset;

	unset = *(ui->test_env);
	while (unset->name != var_to_unset)
	{
		previous = unset;
		unset = unset->next;
	}
	previous->next = unset->next;
	free(unset->name);
	free(unset->value);
	free(unset);
	return (1);
}

void	ft_unset(t_user_input *ui)
{
	t_lexer	*var_to_unset;
	int		exist;
	t_env	*tmp;
	char	*search;

	exist = 0;
	var_to_unset = ui->lexer->next;
	while (var_to_unset && var_to_unset->type == WORD)
	{
		search =var_to_unset->token;
		tmp = *(ui->test_env);
		while (tmp && !exist)
		{
			if (!(__strncmp(tmp->name, search, __strlen(search))))
				exist = ft_unsetvar(ui, tmp->name);
			else
				tmp = tmp->next;
		}
		var_to_unset = var_to_unset->next;
	}
}
