/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:30:48 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/26 10:15:29 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**__free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	tab = NULL;
	return (NULL);
}

void	__clean_input(t_user_input *ui, char **inputs, char *line)
{
	if (ui->token)
		__lstclear(&ui->token, free);
	if (ui->lexer)
		__lexer_clear(&ui->lexer, free);
	__free_tab(inputs);
	free(line);
}